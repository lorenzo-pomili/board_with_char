open Board;

let renderRow = row =>
  Belt.List.mapWithIndex(row, (i, c) =>
    switch (c.character) {
    | None => <CellGUI key={string_of_int(i)} cell=c />
    | Some(character) =>
      <CellGUI key={string_of_int(i)} cell=c>
        <Character key="1" name={character.name} />
      </CellGUI>
    }
  );

let component = ReasonReact.statelessComponent("BoardRowGUI");

let make = (~row: row, _) => {
  ...component,
  render: _ => ReasonReact.array(Array.of_list(renderRow(row))),
};
