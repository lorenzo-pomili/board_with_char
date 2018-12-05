let directionToPath = direction =>
  Board.(
    switch (direction) {
    | Up => <path fill="#00FF00" d="M250 0 L0 500 L500 500 Z" />
    | Down => <path fill="#00FF00" d="M250 500 L0 0 L500 0 Z" />
    | Left => <path fill="#00FF00" d="M0 250 L500 500 L500 0 Z" />
    | Right => <path fill="#00FF00" d="M500 250 L0 500 L0 0 Z" />
    }
  );

let component = ReasonReact.statelessComponent("PathGUI");

let make = (~direction, _) => {
  ...component,
  render: _ =>
    <svg viewBox="0 0 500 500"> {directionToPath(direction)} </svg>,
};
