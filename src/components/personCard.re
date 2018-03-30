let component = ReasonReact.statelessComponent("PersonCard");

let make = (~person: Model.person, _children) => {
  ...component,
  render: _self =>
    <Card>
      <Card.Avatar photoUrl=person.photoUrl />
      <Card.Title
        main=
          <a href="#">
            (
              ReasonReact.stringToElement(
                person.firstname ++ " " ++ person.lastname
              )
            )
          </a>
        sub=(ReasonReact.stringToElement(person.entity))
      />
      <Card.Info icon="email">
        <a href=("mailto:" ++ person.email)>
          (ReasonReact.stringToElement(person.email))
        </a>
      </Card.Info>
      <Card.Info icon="phone">
        <a href=("tel:" ++ person.phone)>
          (ReasonReact.stringToElement(person.phone))
        </a>
      </Card.Info>
      (
        switch person.manager {
        | Some(m) =>
          <Card.Info icon="supervisor_account" desc="manager">
            (ReasonReact.stringToElement(m))
          </Card.Info>
        | None => ReasonReact.nullElement
        }
      )
    </Card>
};