open Board;

let debugCoordStyle =
  ReactDOMRe.Style.make(
    ~backgroundColor="#ff0000",
    ~width="50px",
    ~fontSize="10px",
    ~marginLeft="-20px",
    ~marginTop="-20px",
    ~display="none",
    (),
  );

let cellStyle =
  ReactDOMRe.Style.make(
    ~cursor="pointer",
    ~backgroundColor="#ffffff",
    ~color="#000000",
    ~borderRadius="5px",
    ~padding="20px",
    ~fontSize="150%",
    ~width="50px",
    ~height="50px",
    (),
  );

let getKey = c =>
  string_of_int(c.coord.x) ++ "_" ++ string_of_int(c.coord.y);

let component = ReasonReact.statelessComponent("Cell");

let make = (~cell, ~onClick, children) => {
  ...component,
  render: _ =>
    <div key={getKey(cell)} onClick={_e => onClick(cell)} style=cellStyle>
      <div style=debugCoordStyle>
        <span>
          {ReasonReact.string("y: " ++ string_of_int(cell.coord.y))}
        </span>
        <span>
          {ReasonReact.string(" x: " ++ string_of_int(cell.coord.x))}
        </span>
      </div>
      {ReasonReact.array(children)}
    </div>,
};
