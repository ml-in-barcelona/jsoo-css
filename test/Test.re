open Setup;
open Jsoo_css;
open Properties;
open Colors;

module Dict = {
  /* Dummy implementation of a dictionary */
  type item = (string, string);
  type t = array(item);
  let make = (): t => [||];
  let insert = (key, value, dict): t => {
    Array.append(dict, [|(key, value)|]);
  };
};

module CssForTest = {
  exception NotImplemented;
  include Core.Make({
    let mergeStyles = _ => raise(NotImplemented);
    let injectRules = _ => raise(NotImplemented);
    let injectRaw = _ => raise(NotImplemented);
    let global = (_, _) => raise(NotImplemented);
    let keyframe = (_) => raise(NotImplemented);

    type t = Dict.t;

    let rec ruleToDict = (dict, rule) => {
      switch (rule) {
      | Css.Declaration(name, value) => dict |> Dict.insert(name, value)
      | _ => Dict.make()
      };
    }
    and toJson = (rules: array(Css.rule)): Dict.t =>
      rules |> Array.fold_left(ruleToDict, [||]);

    let make = dict =>
      dict
      |> Array.fold_left(
           (arr, (k, v)) => Array.append(arr, [|k ++ ": " ++ v|]),
           [||],
         )
      |> Array.to_list
      |> String.concat(";");
  });
};

let css = v => CssForTest.make([|v|]);

type testData = {
  name: string,
  cases: list((string, string)),
};

let jsooTestSuitData = [
  {
    name: "color",
    cases: [
      (css(color(rgb(1, 2, 3))), "color: rgb(1, 2, 3)"),
      (css(color(rgba(4, 5, 6, `num(0.3)))), "color: rgba(4, 5, 6, 0.3)"),
      (
        css(color(hsl(deg(7.), pct(8.), pct(9.)))),
        "color: hsl(7deg, 8%, 9%)",
      ),
      (
        css(color(hsla(deg(10.), pct(11.), pct(12.), `num(0.5)))),
        "color: hsla(10deg, 11%, 12%, 0.5)",
      ),
      (
        css(color(hsla(rad(4.7), pct(11.), pct(12.), pct(50.)))),
        "color: hsla(4.7rad, 11%, 12%, 50%)",
      ),
      (css(color(transparent)), "color: transparent"),
      (css(color(hex("FFF"))), "color: #FFF"),
      (css(color(currentColor)), "color: currentColor"),
    ],
  },
  /* {
       name: "Var",
       cases: [
         (css(color(var("--foo"))), "color: var(--foo)"),
         (css(marginTop(var("--bar"))), "margin-top: var(--bar)"),
         (
           css(textDecoration(varDefault("--foo", "default"))),
           "textDecoration: var(--foo,default)",
         ),
         (
           css(alignItems(varDefault("--bar", "default"))),
           "alignItems: var(--bar,default)",
         ),
       ],
     }, */
  {
    name: "Filter",
    cases: [
      /* (css(filter([|`opacity(10.), `invert(20.)|])), "filter: opacity(10%) invert(20%)"), */
      /* (css(filter([`blur(`px(20)), `brightness(20.)])), "filter: blur(20px) brightness(20%)"), */
      /* (css(filter([|`contrast(30.),`dropShadow((`px(5) `px(6) `px(7) `rgb((255 0 0)))) |]), ), "filter: contrast(30%) drop-shadow(5px 6px 7px rgb(255 0 0))"), */
      /* (css(filter([|`grayscale(10.) `hueRotate(`deg(180.))|])),
         "filter: grayscale(10%) hue-rotate(180deg)"), */
      /* (css(filter([|`saturate(10.) `sepia(100.)|])),
         "filter: saturate(10%) sepia(100%)"), */
      (css(filter([|`none|])), "filter: none"),
      (css(filter([|`inherit_|])), "filter: inherit"),
      (css(filter([|`initial|])), "filter: initial"),
      (css(filter([|`unset|])), "filter: unset"),
      (css(filter([|`url("myurl")|])), "filter: url(myurl)"),
    ],
  },
  {
    name: "Angle",
    cases: [
      (css(transform(rotate(deg(1.)))), "transform: rotate(1deg)"),
      (css(transform(rotate(rad(6.28)))), "transform: rotate(6.28rad)"),
      (css(transform(rotate(grad(38.8)))), "transform: rotate(38.8grad)"),
      (css(transform(rotate(turn(0.25)))), "transform: rotate(0.25turn)"),
    ],
  },
  {
    name: "Direction",
    cases: [
      (css(direction(`ltr)), "direction: ltr"),
      (css(direction(ltr)), "direction: ltr"),
      (css(direction(rtl)), "direction: rtl"),
      (css(direction(inherit_)), "direction: inherit"),
      (css(direction(unset)), "direction: unset"),
      (css(direction(initial)), "direction: initial"),
    ],
  },
  {
    name: "Resize",
    cases: [
      (css(resize(none)), "resize: none"),
      (css(resize(both)), "resize: both"),
      (css(resize(horizontal)), "resize: horizontal"),
      (css(resize(vertical)), "resize: vertical"),
      (css(resize(block)), "resize: block"),
      (css(resize(inline)), "resize: inline"),
      (css(resize(inherit_)), "resize: inherit"),
      (css(resize(unset)), "resize: unset"),
      (css(resize(initial)), "resize: initial"),
    ],
  },
  {
    name: "Backdrop filter",
    cases: [
      (css(backdropFilter([|`none|])), "backdropFilter: none"),
      /* (css(backdropFilter([|`blur(`px(10)), `brightness(`percent(42.0))|])), "backdropFilter: blur(10px) brightness(42%)"), */
      /* (css(backdropFilter([|`contrast(`num(10)), `dropShadow(`percent(0.5))|]), ), "backdropFilter: contrast(10) drop-shadow(0.5%)"), */
      /* (css(backdropFilter([|`grayscale(`percent(99.9)), `hueRotate(`deg(90.0)), |]), ), "backdropFilter: grayscale(99.9%) hue-rotate(90deg)"), */
      /* (css(backdropFilter([|`invert(`num(30)), `opacity(`percent(10.0))|])), "backdropFilter: invert(30) opacity(10%)"), */
      /* (css(backdropFilter([|`saturate(`num(30)) `sepia(`percent(10.0))|])), "backdropFilter: saturate(30) sepia(10%)")] */
    ],
  },
  {
    name: "Gradient background",
    cases: [],
    /* (css(background(`linearGradient(deg(45.), [`zero, red, `pct(100.), blue]))), "background: linear-gradient(45deg #FF0000 0 #0000FF 100%)"),
       (css(background(repeatingLinearGradient(deg(45.), [(zero red) (px(10) blue)], ),), ),  "background: repeating-linear-gradient(45deg #FF0000 0 #0000FF) 10px)",
       (css(background(radialGradient([(zero red) (pct(100.) blue)]))),  "background: radial-gradient(#FF0000 0 #0000FF 100%)"),
       css(background(repeatingRadialGradient([(zerored),(Calc.(pct(20.) + px(5))blue),]),),), "background: repeating-radial-gradient(#FF0000 0 #0000FF calc((20%) + 5px))", */
  },
  {
    name: "Position",
    cases: [
      (css(top(px(10))), "top: 10px"),
      (css(right(rem(1.))), "right: 1rem"),
      (css(bottom(pct(20.))), "bottom: 20%"),
      (css(left(vh(4.))), "left: 4vh"),
      (css(top(initial)), "top: initial"),
      (css(right(inherit_)), "right: inherit"),
      (css(bottom(unset)), "bottom: unset"),
      (css(left(initial)), "left: initial"),
    ],
  },
  {
    name: "object-fit",
    cases: [
      (css(objectFit(`fill)), "objectFit: fill"),
      (css(objectFit(`contain)), "objectFit: contain"),
      (css(objectFit(`cover)), "objectFit: cover"),
      (css(objectFit(`none)), "objectFit: none"),
      (css(objectFit(`scaleDown)), "objectFit: scale-down"),
      (css(objectFit(`inherit_)), "objectFit: inherit"),
      (css(objectFit(`initial)), "objectFit: initial"),
      (css(objectFit(`unset)), "objectFit: unset"),
    ],
  },
  {
    name: "box-shadow",
    cases: [
      (css(boxShadow(Shadow.box(green))), "boxShadow: 0 0 0 0 #008000"),
      (
        css(boxShadows([|Shadow.box(yellow), Shadow.box(red)|])),
        "boxShadow: 0 0 0 0 #FFFF00, 0 0 0 0 #FF0000",
      ),
      (
        css(boxShadow(Shadow.box(~x=px(1), ~y=px(2), red))),
        "boxShadow: 1px 2px 0 0 #FF0000",
      ),
      (
        css(boxShadow(Shadow.box(~inset=true, red))),
        "boxShadow: 0 0 0 0 #FF0000 inset",
      ),
      (css(boxShadow(none)), "boxShadow: none"),
      (css(boxShadow(inherit_)), "boxShadow: inherit"),
      (css(boxShadow(initial)), "boxShadow: initial"),
      (css(boxShadow(unset)), "boxShadow: unset"),
      (css(important(boxShadow(none))), "boxShadow: none !important"),
    ],
  },
  {
    name: "text-shadow",
    cases: [
      /* (css(textShadow(Shadow.text(green))), "textShadow: 0 0 0 #008000"),
         (css(textShadows([Shadow.text(yellow) Shadow.text(red)])), "textShadow: 0 0 0 #FFFF00 0 0 0 #FF0000"),
         (css(textShadow(Shadow.text(~x=px(1) ~y=px(2), red))), "textShadow: 1px 2px 0 #FF0000"), */
      /* (css(textShadow(Shadow.text(~blur=vh(1.), `red))), "textShadow: 0 0 1vh #FF0000"), */
      (css(textShadow(none)), "textShadow: none"),
      (css(textShadow(inherit_)), "textShadow: inherit"),
      (css(textShadow(initial)), "textShadow: initial"),
      (css(textShadow(unset)), "textShadow: unset"),
      (css(important(textShadow(none))), "textShadow: none !important"),
    ],
  },
  {
    name: "transitions",
    cases: [
      (css(transition("transform")), "transition: 0ms ease 0ms transform"),
      (
        css(
          transitions([|
            Transition.shorthand("height"),
            Transition.shorthand("top"),
          |]),
        ),
        "transition: 0ms ease 0ms height, 0ms ease 0ms top",
      ),
      (
        css(
          transition(~duration=3, ~delay=4, ~timingFunction=easeOut, "top"),
        ),
        "transition: 3ms ease-out 4ms top",
      ),
    ],
  },
  {
    name: "animation",
    cases: [
      (
        css(
          animation(
            ~duration=300,
            ~delay=400,
            ~direction=reverse,
            ~timingFunction=linear,
            ~fillMode=forwards,
            ~playState=running,
            ~iterationCount=infinite,
            "a",
          ),
        ),
        "animation: a 300ms linear 400ms infinite reverse forwards running",
      ),
    ],
  },
  {
    name: "Word spacing",
    cases: [
      (css(wordSpacing(`normal)), "wordSpacing: normal"),
      (css(wordSpacing(vh(1.))), "wordSpacing: 1vh"),
      (css(wordSpacing(pct(50.))), "wordSpacing: 50%"),
      (css(wordSpacing(inherit_)), "wordSpacing: inherit"),
    ],
  },
  {
    name: "gridTemplateAreas",
    cases: [
      (css(gridTemplateAreas(`none)), "gridTemplateAreas: none"),
      (css(gridTemplateAreas(`areas(["a"]))), "gridTemplateAreas: 'a'"),
      (css(gridTemplateAreas(`inherit_)), "gridTemplateAreas: inherit"),
      /* (css(gridTemplateAreas(`initial)), "gridTemplateAreas: initial") */
      (css(gridTemplateAreas(`unset)), "gridTemplateAreas: unset"),
      (
        css(gridTemplateAreas(`areas(["a a a", "b b b"]))),
        "gridTemplateAreas: 'a a a' 'b b b'",
      ),
    ],
  },
  {
    name: "GridArea",
    cases: [
      (css(gridArea(`auto)), "gridArea: auto"),
      (css(gridArea(`ident("a"))), "gridArea: a"),
      (css(gridArea(`num(1))), "gridArea: 1"),
      /* (css(gridArea(`numIdent((1 "a")))), "gridArea: 1 a"), */
      (css(gridArea(`span(`num(1)))), "gridArea: span 1"),
      (css(gridArea(`span(`ident("a")))), "gridArea: span a"),
      (css(gridArea(`inherit_)), "gridArea: inherit"),
      (css(gridArea(`initial)), "gridArea: initial"),
      (css(gridArea(`unset)), "gridArea: unset"),
      /* (css(gridArea2(`auto `num(1))), "gridArea: auto / 1"), */
      /* (css(gridArea3(`ident("a") `numIdent((1 "a")) `auto)), "gridArea: a / 1 a / auto"), */
      /* (css(gridArea4(`num(5) `span(`num(16)) `span(`ident("b")) `auto), "gridArea: 5 / span 16 / span b / auto"), */
    ],
  },
  {
    name: "gridTemplateCoumns",
    cases: [],
    /* (css(gridTemplateColumns([`fr(1.) `px(100) `auto])), "gridTemplateColumns: 1fr 100px auto"),
       (css(gridTemplateColumns([`repeat((`num(4) `fr(1.)))])), "gridTemplateColumns: repeat(4 1fr)"),
       (css(gridTemplateColumns([`repeat((`num(4) `auto))])), "gridTemplateColumns: repeat(4 auto)"),
       (css(gridTemplateColumns([`repeat((`num(4) `minContent))])), "gridTemplateColumns: repeat(4 min-content)"),
       (css(gridTemplateColumns([`repeat((`num(4) `maxContent))])), "gridTemplateColumns: repeat(4 max-content)"),
       (css(gridTemplateColumns([ `repeat((`num(4) `minmax((`px(100) `fr(1.)))))]), "gridTemplateColumns: repeat(4 minmax(100px,1fr))"), */
  },
  {
    name: "backgroundPosition",
    cases: [
      (css(backgroundPosition(`left)), "backgroundPosition: left"),
      (css(backgroundPosition(`right)), "backgroundPosition: right"),
      (css(backgroundPosition(`top)), "backgroundPosition: top"),
      (css(backgroundPosition(`bottom)), "backgroundPosition: bottom"),
      (css(backgroundPosition(center)), "backgroundPosition: center"),
      (css(backgroundPosition(pct(50.))), "backgroundPosition: 50%"),
      (css(backgroundPosition(initial)), "backgroundPosition: initial"),
      (css(backgroundPosition(inherit_)), "backgroundPosition: inherit"),
      (css(backgroundPosition(unset)), "backgroundPosition: unset"),
      (
        css(backgroundPosition(`hv((`left, center)))),
        "backgroundPosition: left center",
      ),
      (
        css(backgroundPosition(`hv((`right, pct(50.))))),
        "backgroundPosition: right 50%",
      ),
      (
        css(backgroundPosition(`hv((pct(50.), `top)))),
        "backgroundPosition: 50% top",
      ),
      (
        css(backgroundPosition(`hv((pct(50.), pct(50.))))),
        "backgroundPosition: 50% 50%",
      ),
      (
        css(backgroundPositions([|`hv((px(0), px(0)))|])),
        "backgroundPosition: 0px 0px",
      ),
      (
        css(
          backgroundPosition4(
            ~y=`top,
            ~offsetY=px(10),
            ~x=`right,
            ~offsetX=px(50),
          ),
        ),
        "backgroundPosition: right 50px top 10px",
      ),
    ],
  },
  {
    name: "backgroundRepeat",
    cases: [
      (css(backgroundRepeat(repeatX)), "backgroundRepeat: repeat-x"),
      (css(backgroundRepeat(repeatY)), "backgroundRepeat: repeat-y"),
      (css(backgroundRepeat(repeat)), "backgroundRepeat: repeat"),
      (css(backgroundRepeat(space)), "backgroundRepeat: space"),
      (css(backgroundRepeat(round)), "backgroundRepeat: round"),
      (css(backgroundRepeat(noRepeat)), "backgroundRepeat: no-repeat"),
      (css(backgroundRepeat(inherit_)), "backgroundRepeat: inherit"),
      (
        css(backgroundRepeat(`hv((repeat, space)))),
        "backgroundRepeat: repeat, space",
      ),
      (
        css(backgroundRepeat(`hv((repeat, repeat)))),
        "backgroundRepeat: repeat, repeat",
      ),
      (
        css(backgroundRepeat(`hv((round, space)))),
        "backgroundRepeat: round, space",
      ),
      (
        css(backgroundRepeat(`hv((noRepeat, round)))),
        "backgroundRepeat: no-repeat, round",
      ),
    ],
  },
  {
    name: "backgroundImage",
    cases: [
      (css(backgroundImage(none)), "backgroundImage: none"),
      /* (css(backgroundImage(url("x"))), "backgroundImage: url(x)"), */
      /* (
           css(backgroundImage(linearGradient(deg(5.), [(pct(10.), red)]))),
           "backgroundImage: linear-gradient(5deg #FF0000 10%)",
         ), */
      /* (
           css(
             backgroundImage(
               repeatingLinearGradient(rad(6.), [(pct(20.), black)]),
             ),
           ),
           "backgroundImage: repeating-linear-gradient(6rad #000000 20%)",
         ),
         (
           css(backgroundImage(radialGradient([(pct(30.), yellow)]))),
           "backgroundImage: radial-gradient(#FFFF00 30%)",
         ),
         (
           css(
             backgroundImage(repeatingRadialGradient([(pct(30.), yellow)])),
           ),
           "backgroundImage: repeating-radial-gradient(#FFFF00 30%)",
         ), */
    ],
  },
  {
    name: "background shorhand",
    cases: [
      (css(background(rgb(1, 2, 3))), "background: rgb(1, 2, 3)"),
      /* (css(background(url("x"))), "background: url(x)"), */
      /* (
           css(background(linearGradient(red, rgre))),
           "background: linear-gradient(5deg, #FF0000, 10%)",
         ), */
      (css(background(none)), "background: none"),
    ],
  },
  {
    name: "clipPath",
    cases: [
      (css(clipPath(none)), "clipPath: none"),
      /* (css(clipPath(url("x"))), "clipPath: url(x)"), */
      (css(clipPath(marginBox)), "clipPath: margin-box"),
      (css(clipPath(borderBox)), "clipPath: border-box"),
      (css(clipPath(paddingBox)), "clipPath: padding-box"),
      (css(clipPath(contentBox)), "clipPath: content-box"),
      (css(clipPath(fillBox)), "clipPath: fill-box"),
      (css(clipPath(strokeBox)), "clipPath: stroke-box"),
      (css(clipPath(viewBox)), "clipPath: view-box"),
      (css(clipPath(inherit_)), "clipPath: inherit"),
      (css(clipPath(initial)), "clipPath: initial"),
      (css(clipPath(unset)), "clipPath: unset"),
    ],
  },
  {
    name: "columnGap",
    cases: [
      (css(columnGap(normal)), "columnGap: normal"),
      (css(columnGap(px(3))), "columnGap: 3px"),
      (css(columnGap(em(2.5))), "columnGap: 2.5em"),
      (css(columnGap(pct(3.))), "columnGap: 3%"),
      (css(columnGap(inherit_)), "columnGap: inherit"),
      (css(columnGap(initial)), "columnGap: initial"),
      (css(columnGap(unset)), "columnGap: unset"),
    ],
  },
  {
    name: "cursor",
    cases: [
      (css(cursor(contextMenu)), "cursor: context-menu"),
      (css(cursor(help)), "cursor: help"),
      (css(cursor(pointer)), "cursor: pointer"),
      (css(cursor(progress)), "cursor: progress"),
      (css(cursor(wait)), "cursor: wait"),
      (css(cursor(cell)), "cursor: cell"),
      (css(cursor(crosshair)), "cursor: crosshair"),
      (css(cursor(text)), "cursor: text"),
      (css(cursor(verticalText)), "cursor: vertical-text"),
      (css(cursor(alias)), "cursor: alias"),
      (css(cursor(copy)), "cursor: copy"),
      (css(cursor(move)), "cursor: move"),
      (css(cursor(noDrop)), "cursor: no-drop"),
      (css(cursor(notAllowed)), "cursor: not-allowed"),
      (css(cursor(grab)), "cursor: grab"),
      (css(cursor(grabbing)), "cursor: grabbing"),
      (css(cursor(allScroll)), "cursor: all-scroll"),
      (css(cursor(colResize)), "cursor: col-resize"),
      (css(cursor(rowResize)), "cursor: row-resize"),
      (css(cursor(nResize)), "cursor: n-resize"),
      (css(cursor(eResize)), "cursor: e-resize"),
      (css(cursor(sResize)), "cursor: s-resize"),
      (css(cursor(wResize)), "cursor: w-resize"),
      (css(cursor(neResize)), "cursor: ne-resize"),
      (css(cursor(nwResize)), "cursor: nw-resize"),
      (css(cursor(seResize)), "cursor: se-resize"),
      (css(cursor(swResize)), "cursor: sw-resize"),
      (css(cursor(ewResize)), "cursor: ew-resize"),
      (css(cursor(nsResize)), "cursor: ns-resize"),
      (css(cursor(neswResize)), "cursor: nesw-resize"),
      (css(cursor(nwseResize)), "cursor: nwse-resize"),
      (css(cursor(zoomIn)), "cursor: zoom-in"),
      (css(cursor(zoomOut)), "cursor: zoom-out"),
    ],
  },
  {
    name: "counter",
    cases: [
      (css(counterReset(none)), "counterReset: none"),
      (css(counterReset(`reset(("foo", 2)))), "counterReset: foo 2"),
      (css(counterReset(var("bar"))), "counterReset: var(--bar)"),
      (css(counterSet(none)), "counterSet: none"),
      (css(counterSet(`set(("foo", 2)))), "counterSet: foo 2"),
      (css(counterSet(var("bar"))), "counterSet: var(--bar)"),
      (css(counterIncrement(none)), "counterIncrement: none"),
      (
        css(counterIncrement(`increment(("foo", 2)))),
        "counterIncrement: foo 2",
      ),
      (css(counterIncrement(var("bar"))), "counterIncrement: var(--bar)"),
    ],
  },
];

describe("Jsoo Test Suit", _ => {
  jsooTestSuitData
  |> List.iter(data => {
       describe(data.name, ({test, _}) => {
         data.cases
         |> List.iter(case => {
              let input = fst(case);
              let out = snd(case);
              test("should render " ++ out, ({expect, _}) => {
                expect.string(input).toEqual(out)
              });
            })
       })
     })
});
