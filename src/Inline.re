open Core;
include Values;
include Properties;
include Colors;

include Make({
  type t = Js_of_ocaml.Js.json;
  exception NotImplemented;

  let toJson = Core.toJson;
  let make = (. _) => raise(NotImplemented);
  let mergeStyles = (. _) => raise(NotImplemented);
  let injectRule = (. _) => ();
  let injectRaw = (. _) => ();
});

external unsafeJsonToStyles: Js_of_ocaml.Js.json => React.Dom.style =
  "%identity";
let style = (. rules) => rules |> toJson |> unsafeJsonToStyles;
