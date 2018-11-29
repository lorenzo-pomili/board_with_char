open Board;

let getCells = characterPos =>
  Belt.List.map(makeCells(default_edge * default_edge), v =>
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
    ~gridTemplateColumns=getGridTemplateColumns(default_edge, "90px"),
    ~gridGap="10px",
    ~backgroundColor="#000000",
    ~color="#444444",
    ~padding="10px",
    (),
  );

let getCharPos = c => c.x + default_edge * c.y;

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
