open Js_of_ocaml;

include Core;
include Colors;

include Core.Make({
  [@bs.module "emotion"]
  external mergeStyles: (. array(string)) => string = "cx";

  [@bs.module "emotion"] external make: (. Js.json) => string = "css";

  [@bs.module "emotion"]
  external injectRule: (. Js.json) => unit = "injectGlobal";

  [@bs.module "emotion"]
  external injectRaw: (. string) => unit = "injectGlobal";

  [@bs.module "emotion"]
  external makeKeyFrames: (. Js.t(Js.json)) => string = "keyframes";
});

/* TODO:
   Why is cache needed?
    type cache;

    [@bs.module "emotion"] external cache: cache = "cache";
    */

/*
 TODO: Do we still need this?
 let fontFace =
        (~fontFamily, ~src, ~fontStyle=?, ~fontWeight=?, ~fontDisplay=?, ()) => {
      insertRule(.
        Css_Js_Core.fontFace(
          ~fontFamily,
          ~src,
          ~fontStyle?,
          ~fontWeight?,
          ~fontDisplay?,
          (),
        ),
      );
      fontFamily;
    };
     */
