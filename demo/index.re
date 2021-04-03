module App = {
  open Jsoo_css;
  open Emotion;
  let app =
    Emotion.make([|
      display(`flex),
      width(px(1050)),
      flexDirection(`column),
      alignItems(`center),
      padding(px(80)),
    |]);
  let h2 =
    Inline.style([|padding2(~v=`px(10), ~h=`px(5)), color(Colors.grey)|]);

  let h1 = Inline.style([|color(`rgb((123, 123, 123)))|]);

  let box =
    Emotion.make([|
      color(`hex("333")),
      backgroundColor(`hex("C0FFEE")),
      padding(px(45)),
      borderRadius(px(8)),
      fontSize(px(22)),
      fontWeight(`bold),
    |]);

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
