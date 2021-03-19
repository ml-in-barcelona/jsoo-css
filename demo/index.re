module App = {
  open Jsoo_css;
  open Jsoo_css.Core;
  let rowLayout =
    Inline.style([|
      display(`flex),
      flexDirection(`row),
      padding2(~v=`px(10), ~h=`px(5)),
      backgroundColor(`hex("333")),
      color(Colors.white),
      borderRadius(`px(4)),
    |]);

  let h1 = Inline.style([|color(`rgb((123, 123, 123)))|]);
  let h2 = Emotion.make([|color(`hex("C0FFEE"))|]);

  [@react.component]
  let make = () => {
    <div className="App">
      <h1 style=h1> {React.string("Hello CodeSandbox")} </h1>
      <h2 className=h2>
        {React.string("Start editing to see some magic happen!")}
      </h2>
      <div style=rowLayout> {React.string("Flexing")} </div>
    </div>;
  };
};

React.Dom.renderToElementWithId(<App />, "demo");
