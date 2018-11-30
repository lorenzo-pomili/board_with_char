open Board;

let getGridTemplateColumns = (n, size) => Js.String.repeat(n, size ++ " ");

let boardStyle =
  ReactDOMRe.Style.make(
    ~display="grid",
    ~gridTemplateColumns=getGridTemplateColumns(default_edge + 1, "90px"),
    ~gridGap="10px",
    ~backgroundColor="#000000",
    ~color="#444444",
    ~padding="10px",
    (),
  );

let getCharPos = c => c.x + default_edge * c.y;

type state = {character};

type action =
  | MoveTo(coord)
  | ChangeCoord(direction);

let move = (send, d) => send(ChangeCoord(d));

let moveOnKeyDown = (send, e) =>
  switch (ReactEvent.Keyboard.key(e)) {
  | "ArrowUp" => move(send, Up)
  | "ArrowDown" => move(send, Down)
  | "ArrowLeft" => move(send, Left)
  | "ArrowRight" => move(send, Right)
  | _ => ()
  };

let renderBoard = (board, moveTo) =>
  Belt.List.mapWithIndex(board, (i, row) =>
    <BoardRowGUI key={string_of_int(i)} onCellClick=moveTo row />
  );

let board = makeBoard(default_edge);

let char1 = getNewCharacter("Me", {x: 0, y: 0});

let boardWithCharacter = getBoardWithCharacter(board, char1);

let moveTo = (send, cell) => send(MoveTo(cell.coord));

let component = ReasonReact.reducerComponent("Board");

let make = _ => {
  ...component,
  initialState: () => {character: getNewCharacter("Me", {x: 0, y: 0})},
  reducer: (action, state) =>
    switch (action) {
    | ChangeCoord(d) =>
      ReasonReact.Update({
        character: {
          ...state.character,
          coord: getNewCood(state.character.coord, d),
        },
      })
    | MoveTo(coord) =>
      ReasonReact.Update({
        character: {
          ...state.character,
          coord,
        },
      })
    },
  render: ({state, send}) =>
    <div style=boardStyle tabIndex=0 onKeyDown={e => moveOnKeyDown(send, e)}>
      {
        ReasonReact.array(
          Array.of_list(
            renderBoard(
              getBoardWithCharacter(board, state.character),
              moveTo(send),
            ),
          ),
        )
      }
    </div>,
};
