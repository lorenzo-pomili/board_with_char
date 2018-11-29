let component = ReasonReact.statelessComponent("Character");

let make = (~name, _) => {
  ...component,
  render: _ => ReasonReact.string(name),
};
