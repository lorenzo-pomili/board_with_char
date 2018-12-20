open Board;

let renderRow = (row, onCellClick) =>
  Belt.List.mapWithIndex(row, (i, c) =>
    <CellGUI key={string_of_int(i)} cell=c onClick=onCellClick>
      {switch (c.element) {
       | None => ReasonReact.null
       | Some(Character(character)) =>
         <Character moving={character.moving} key="1" name={character.name} />
       | Some(Path(path)) => <PathGUI key="1" direction={path.direction} />
       }}
    </CellGUI>
  );

let component = ReasonReact.statelessComponent("BoardRowGUI");

let make = (~row: row, ~onCellClick, _) => {
  ...component,
  render: _ =>
    ReasonReact.array(Array.of_list(renderRow(row, onCellClick))),
};
