open Js_of_ocaml;

include Core;
include Colors;

include Core.Make({
  [@js.global "emotion"]
  external mergeStyles: (. array(string)) => string = "cx";

  [@js.global "emotion"] external make: (. Js.json) => string = "css";

  [@js.global "emotion"]
  external injectRule: (. Js.json) => unit = "injectGlobal";

  [@js.global "emotion"]
  external injectRaw: (. string) => unit = "injectGlobal";

  [@js.global "emotion"]
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
