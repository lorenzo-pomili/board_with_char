open Board;

let characterMoveDelay = 1000;

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

type state = {
  character,
  currentPath: option(path),
};

type action =
  | StopMove
  | MoveTo(coord, direction)
  | SetPath(coord, coord)
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

let renderBoard = (board, setPath) =>
  Belt.List.mapWithIndex(board, (i, row) =>
    <BoardRowGUI key={string_of_int(i)} onCellClick=setPath row />
  );

let board = makeBoard(default_edge);

let char1 = getNewCharacter("Me", {x: 0, y: 0});

let setPath = (send, character: character, cell) =>
  send(SetPath(character.coord, cell.coord));

let moveViaPath = (send, path: Board.path) => {
  let rec aux = (p: Board.path) =>
    switch (p) {
    | [] => send(StopMove)
    | [ph, ...pr] =>
      send(StopMove);
      send(MoveTo(ph.coord, ph.direction));
      Js.Global.setTimeout(() => aux(pr), characterMoveDelay) |> ignore;
    };
  aux(path);
};

let moveTo = (send, character: character, currentPath, cell) =>
  switch (currentPath) {
  | None => setPath(send, character, cell)
  | Some(path) =>
    if (coordIsPathArrival(path, cell.coord)) {
      moveViaPath(send, path);
    } else {
      setPath(send, character, cell);
    }
  };

let component = ReasonReact.reducerComponent("Board");

let make = _ => {
  ...component,
  initialState: () => {
    character: getNewCharacter("Me", {x: 0, y: 0}),
    currentPath: None,
  },
  reducer: (action, state) =>
    switch (action) {
    | StopMove =>
      ReasonReact.Update({
        ...state,
        character: {
          ...state.character,
          moving: None,
        },
      })
    | ChangeCoord(d) =>
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          character: {
            ...state.character,
            coord: getNewCood(state.character.coord, d),
            moving: Some(d),
          },
        },
        (
          ({send}) =>
            Js.Global.setTimeout(() => send(StopMove), 250) |> ignore
        ),
      )
    | MoveTo(coord, d) =>
      ReasonReact.Update({
        character: {
          ...state.character,
          moving: Some(d),
          coord,
        },
        currentPath: None,
      })
    | SetPath(c1, c2) =>
      ReasonReact.Update({...state, currentPath: Some(findPath(c1, c2))})
    },
  render: ({state, send}) =>
    <div style=boardStyle tabIndex=0 onKeyDown={e => moveOnKeyDown(send, e)}>
      {
        ReasonReact.array(
          Array.of_list(
            renderBoard(
              getBoardWithElements(
                board,
                [
                  Character(state.character),
                  ...pathToBoardElements(
                       Belt.Option.getWithDefault(state.currentPath, []),
                     ),
                ],
              ),
              moveTo(send, state.character, state.currentPath),
            ),
          ),
        )
      }
    </div>,
};
