let directionToString = direction =>
  Board.(
    switch (direction) {
    | Up => "^"
    | Down => "\/"
    | Left => "<="
    | Right => "=>"
    }
  );

let component = ReasonReact.statelessComponent("PathGUI");

let make = (~direction, _) => {
  ...component,
  render: _ =>
    <div> {ReasonReact.string(directionToString(direction))} </div>,
};
