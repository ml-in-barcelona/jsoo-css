# jsoo-css

jsoo-css gives a complementary API for dealing with styles in jsoo. Provides `Inline` and `Emotion` implementations to deal with inline styles or use [emotion.sh](https://emotion.sh) to enable CSS-in-JS mechanism. Plays really well with [jsoo-react](https://github.com/jchavarri/jsoo-react).

### Example

```reason
module App = {
  open Jsoo_css;
  open Jsoo_css.Core;

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
```

## Instalation

1. Install jsoo-css directly from github (currently not published on opam)
```sh
opam pin add -y jsoo-css https://github.com/reason-in-barcelona/jsoo-css.git
```

2. Add `jsoo-css` library on your executable stanza with `modes js`
```
(executables
(names index)
(modes js)
(libraries jsoo-css))
```

3. Provide global emotion dependency with `(js_of_ocaml (javascript_files globals.js))`
```js
// globals.js
joo_global_object.emotion = require("@emotion/css");
```

### Acknowledgements

This project is based on [bs-css](https://github.com/reasonml-labs/bs-css), so, many thanks to [@giraud](https://github.com/giraud).
Thanks to [bs-declaredom](https://github.com/Risto-Stevcev/bs-declaredom) for such a precise HTML and CSS implementation for BuckleScript.
Thanks to [elm-css](https://github.com/rtfeldman/elm-css) for being an inspiration.
