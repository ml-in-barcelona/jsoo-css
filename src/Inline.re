open Js_of_ocaml;

include Core;
include Colors;

include Core.Make({
  exception NotImplemented;

  let make = (. _) => raise(NotImplemented);
  let mergeStyles = (. _) => raise(NotImplemented);
  let injectRule = (. _) => ();
  let injectRaw = (. _) => ();
  let makeKeyFrames = (. _) => raise(NotImplemented);
});

external unsafeJsonToStyles: Js.json => React.Dom.style = "%identity";
let style = (. rules) => rules |> toJson |> unsafeJsonToStyles;
