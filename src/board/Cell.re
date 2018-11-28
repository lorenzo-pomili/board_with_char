let cellStyle =
  ReactDOMRe.Style.make(
    ~backgroundColor="#ffffff",
    ~color="#000000",
    ~borderRadius="5px",
    ~padding="20px",
    ~fontSize="150%",
    (),
  );
let component = ReasonReact.statelessComponent("Cell");

let make = children => {
  ...component,
  render: _ => <div style=cellStyle> {ReasonReact.array(children)} </div>,
};
