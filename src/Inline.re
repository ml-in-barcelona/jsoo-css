include Values;
include Properties;
include Colors;
include Core;

include Core.Make({
  type t = Js_of_ocaml.Js.json;
  exception NotImplemented;

  let toJson = Css.toJson;
  let make = (. _) => raise(NotImplemented);
  let mergeStyles = (. _) => raise(NotImplemented);
  let injectRules = (. _, _) => ();
  let injectRaw = (. _) => ();
  let global = (. _, _) => ();
  let keyframe = (. _) => raise(NotImplemented)
});

external unsafeJsonToStyles: Js_of_ocaml.Js.json => React.Dom.Style.t =
  "%identity";

let style = (. rules) => rules |> Css.toJson |> unsafeJsonToStyles;
