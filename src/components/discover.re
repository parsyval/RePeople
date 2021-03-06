WebPack.require("./discover.css");

module Fab = {
  let component = ReasonReact.statelessComponent("Fab");
  let make = (~kind, ~size=?, ~onClick, _children) => {
    let sizeClass =
      switch size {
      | Some(s) => " btn-" ++ s
      | None => ""
      };
    {
      ...component,
      render: (_) =>
        <a
          className=(
            "btn-default btn-floating waves-effect waves-light" ++ sizeClass
          )
          onClick>
          <i className="material-icons">
            (ReasonReact.stringToElement(kind))
          </i>
        </a>
    };
  };
};

type actions =
  | ShowNext
  | ShowPrev
  | Play
  | Pause;

type state = {
  currentPersonId: int,
  isPlaying: bool,
  intervalId: ref(option(Js.Global.intervalId))
};

let initialState = () => {
  currentPersonId: 1,
  isPlaying: false,
  intervalId: ref(None)
};

let succ = (max, n) => n >= max ? 1 : n + 1;

let pred = (max, n) => n <= 1 ? max : n - 1;

let setNext = (nbPeople, state) => {
  ...state,
  currentPersonId: succ(nbPeople, state.currentPersonId)
};

let setPrev = (nbPeople, state) => {
  ...state,
  currentPersonId: pred(nbPeople, state.currentPersonId)
};

let setPlaying = (isPlaying, state) => {...state, isPlaying};

let stopInterval = ({ReasonReact.state}) =>
  switch state.intervalId^ {
  | Some(iid) =>
    Js.Global.clearInterval(iid);
    state.intervalId := None;
  | None => ()
  };

let startInterval = ({ReasonReact.state, send} as self) => {
  stopInterval(self);
  state.intervalId := Some(Js.Global.setInterval(() => send(ShowNext), 2000));
};

let reducer = (nbPeople, action, state) =>
  ReasonReact.(
    switch action {
    | ShowNext => Update(state |> setNext(nbPeople))
    | ShowPrev => Update(state |> setPrev(nbPeople))
    | Play =>
      UpdateWithSideEffects(
        state |> setNext(nbPeople) |> setPlaying(true),
        startInterval
      )
    | Pause => UpdateWithSideEffects(state |> setPlaying(false), stopInterval)
    }
  );

let component = ReasonReact.reducerComponent("Discover");

let make = (~people, _children) => {
  let aPeople = Array.of_list(people);
  let nbPeople = Array.length(aPeople);
  {
    ...component,
    initialState,
    reducer: reducer(nbPeople),
    willUnmount: stopInterval,
    render: ({state, send}) =>
      <div className="Discover">
        <div className="card-container">
          <PersonCard person=aPeople[state.currentPersonId - 1] />
        </div>
        <div className="fab-container">
          <Fab kind="skip_previous" onClick=(__ => send(ShowPrev)) />
          (
            state.isPlaying ?
              <Fab kind="pause" size="large" onClick=(__ => send(Pause)) /> :
              <Fab kind="play_arrow" size="large" onClick=(__ => send(Play)) />
          )
          <Fab kind="skip_next" onClick=(__ => send(ShowNext)) />
        </div>
      </div>
  };
};