Utils.import "style/card.css";

let component = ReasonReact.statelessComponent "Card";

let make children => {
  ...component,
  render: fun _self =>
    <div className="Card card">
      (ReasonReact.createDomElement "div" props::{"className": "card-content"} children)
    </div>
};

module Title = {
  let component = ReasonReact.statelessComponent "Card.Title";
  let make ::main ::sub _children => {
    ...component,
    render: fun _self =>
      <div className="card-title">
        <div> main </div>
        <div className="card-subtitle"> sub </div>
      </div>
  };
};

module Avatar = {
  let component = ReasonReact.statelessComponent "Card.Avatar";
  let make ::photoUrl ::altText="persons face" _children => {
    ...component,
    render: fun _self => <img className="card-avatar" src=photoUrl alt=altText />
  };
};

module Info = {
  let component = ReasonReact.statelessComponent "Card.Info";
  let make ::icon ::desc=? children => {
    ...component,
    render: fun _self =>
      <div className="card-info">
        <i
          className="material-icons"
          title=(
            switch desc {
            | Some d => d
            | None => icon
            }
          )>
          (ReasonReact.stringToElement icon)
        </i>
        (ReasonReact.createDomElement "span" props::(Js.Obj.empty ()) children)
      </div>
  };
};
