let component = ReasonReact.statelessComponent("Character");

let getCharStyle = moving =>
  switch (moving) {
  | None => ReactDOMRe.Style.make(~backgroundColor="", ())
  | Some(_d) => ReactDOMRe.Style.make(~backgroundColor="red", ())
  };

let make = (~name, ~moving, _) => {
  ...component,
  render: _ =>
    <span style={getCharStyle(moving)}> {ReasonReact.string(name)} </span>,
};
