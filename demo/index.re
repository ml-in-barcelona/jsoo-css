open Jsoo_css;

Emotion.(global(. "h1, h2, h3", [|color(rgb(33, 33, 33))|]));

let fadeIn = Emotion.(keyframe(.
  [|
    (0, [|transform(scale(0.1, 0.1)), opacity(0.0)|]),
    (60, [|transform(scale(1.2, 1.2)), opacity(1.0)|]),
    (100, [|transform(scale(1.0, 1.0)), opacity(1.0)|]),
  |])
);

module App = {
  let app =
    Emotion.(make([|
      display(`flex),
      width(px(1050)),
      flexDirection(`column),
      alignItems(`center),
      padding(px(80)),
    |]));

  let h2 =
    Inline.(style([|padding2(~v=`px(10), ~h=`px(5)), color(Colors.grey)|]));

  let h1 = Inline.(style([|color(`rgb((123, 123, 123)))|]));

  let box =
    Emotion.(make([|
      color(`hex("333")),
      backgroundColor(`hex("C0FFEE")),
      padding(px(45)),
      borderRadius(px(8)),
      fontSize(px(22)),
      fontWeight(`bold),
    |]));

  [@react.component]
  let make = () => {
    <div className=app>
      <h1 style=h1> {React.string({|Hello OCamler 🐫|})} </h1>
      <h2 style=h2>
        {React.string("Welcome to the world of React & CSS-in-JS")}
      </h2>
      <div className=box>
        {React.string("This is a title styled with emotion.sh")}
      </div>
    </div>;
  };
};

React.Dom.renderToElementWithId(<App />, "demo");
