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
    [@@js.custom
    val make_internal :
      Imports.emotion -> style -> string
      [@@js.call "css"]

    let make style = make_internal Imports.emotion style]

  val injectRules: string -> style -> unit
    [@@js.custom
    val inject_rule_internal :
      Imports.emotion -> string -> style -> unit
      [@@js.call "injectGlobal"]

    let injectRules selector style = inject_rule_internal Imports.emotion selector style]

  val injectRaw: string -> unit
  [@@js.custom
    val inject_global_internal :
      Imports.emotion -> string -> unit
      [@@js.call "injectGlobal"]

    let injectRaw style = inject_global_internal Imports.emotion style
  ]

  val keyframe: Ojs.t -> string
  [@@js.custom
    val keyframes_internal :
      Imports.emotion -> Ojs.t -> string
      [@@js.call "keyframes"]

    let keyframe frames = keyframes_internal Imports.emotion frames
  ]

  val mergeStyles: string array -> string
    [@@js.custom
    val cx_internal :
      Imports.emotion -> string array -> string
      [@@js.call "cx"]

    let mergeStyles declarations = cx_internal Imports.emotion declarations]
