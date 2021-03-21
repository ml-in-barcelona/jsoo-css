[@@@js.stop]
  type style = Js_of_ocaml.Js.json
  val style_to_js : style -> Ojs.t
  val style_of_js : Ojs.t -> style
[@@@js.start]

[@@@js.implem
  type style = Js_of_ocaml.Js.json
  external style_to_js: style -> Ojs.t = "%identity"
  external style_of_js: Ojs.t -> style = "%identity"]

  val make: style -> string
    [@@js.global "emotion.css"]

  val injectRule: style -> unit
    [@@js.global "emotion.injectGlobal"]

  val injectRaw: string -> unit
    [@@js.global "emotion.injectGlobal"]

  (* val makeKeyFrames: style Js_of_ocaml.Js.t -> string
    [@@js.global "emotion.keyframes"] *)

  val mergeStyles: string array -> string
    [@@js.global "emotion.cx"]