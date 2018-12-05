open Board;

let renderRow = (row, onCellClick) =>
  Belt.List.mapWithIndex(row, (i, c) =>
    switch (c.element) {
    | None => <CellGUI key={string_of_int(i)} onClick=onCellClick cell=c />
    | Some(Character(character)) =>
      <CellGUI key={string_of_int(i)} cell=c onClick=onCellClick>
        <Character key="1" name={character.name} />
      </CellGUI>
    | Some(Path(path)) =>
      <CellGUI key={string_of_int(i)} cell=c onClick=onCellClick>
        <PathGUI key="1" direction={path.direction} />
      </CellGUI>
    }
  );

let component = ReasonReact.statelessComponent("BoardRowGUI");

let make = (~row: row, ~onCellClick, _) => {
  ...component,
  render: _ =>
    ReasonReact.array(Array.of_list(renderRow(row, onCellClick))),
};
