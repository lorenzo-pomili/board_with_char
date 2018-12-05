let component = ReasonReact.statelessComponent("PathGUI");

let make = (~direction, _) => {
  ...component,
  render: _ => <div> {ReasonReact.string(direction)} </div>,
};
