let makeCells = n => {
  let rec aux = (acc, x) =>
    if (x < 0) {
      acc;
    } else {
      aux([x, ...acc], x - 1);
    };
  aux([], n - 1);
};

let getCells = characterPos =>
  Belt.List.map(makeCells(64), v =>
    if (v == characterPos) {
      <Cell key={string_of_int(v)}> <Character key="1" name="Me" /> </Cell>;
    } else {
      <Cell key={string_of_int(v)} />;
    }
  );

let getGridTemplateColumns = (n, size) => Js.String.repeat(n, size ++ " ");

let boardStyle =
  ReactDOMRe.Style.make(
    ~display="grid",
    ~gridTemplateColumns=getGridTemplateColumns(8, "100px"),
    ~gridGap="10px",
    ~backgroundColor="#000000",
    ~color="#444444",
    (),
  );

type coord = {
  x: int,
  y: int,
};

type direction =
  | Up
  | Down
  | Left
  | Right;

let getCharPos = c => c.x + 8 * c.y;

let getNewCood = (coord, direction) =>
  switch (direction) {
  | Up =>
    if (coord.y == 0) {
      coord;
    } else {
      {...coord, y: coord.y - 1};
    }
  | Down =>
    if (coord.y == 7) {
      coord;
    } else {
      {...coord, y: coord.y + 1};
    }
  | Left =>
    if (coord.x == 0) {
      coord;
    } else {
      {...coord, x: coord.x - 1};
    }
  | Right =>
    if (coord.x == 7) {
      coord;
    } else {
      {...coord, x: coord.x + 1};
    }
  };

type state = {currenCoord: coord};

type action =
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

let component = ReasonReact.reducerComponent("Board");

let make = _ => {
  ...component,
  initialState: () => {
    currenCoord: {
      x: 0,
      y: 0,
    },
  },
  reducer: (action, state) =>
    switch (action) {
    | ChangeCoord(d) =>
      ReasonReact.Update({currenCoord: getNewCood(state.currenCoord, d)})
    },
  render: ({state, send}) =>
    <div style=boardStyle tabIndex=0 onKeyDown={e => moveOnKeyDown(send, e)}>
      {
        ReasonReact.array(
          Array.of_list(getCells(getCharPos(state.currenCoord))),
        )
      }
    </div>,
};
