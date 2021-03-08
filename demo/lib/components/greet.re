module Model = {
  [@deriving sexp_of]
  type t = int;

  let cutoff: (t, t) => bool = ((==): (t, t) => bool);

  let empty = 0;
};

module State = {
  [@deriving sexp_of]
  type t = unit;
};

module Action = {
  [@deriving sexp_of]
  type t =
    | Increment
    | Decrement;

  let apply = (model, action, _state, ~schedule_action as _) =>
    switch (action) {
    | Increment => model + 1
    | Decrement => model - 1
    };
};

let on_startup = (~schedule_action as _, _): Async_kernel.Deferred.t(State.t) =>
  Async_kernel.return();

let view = (model, ~inject) =>
  Incr_dom.Tyxml.Html.(
    div(
      ~a=[a_class(["greet__container"])],
      [
        p(
          ~a=[a_class(["greet__welcome-message"])],
          [
            txt("👋 Welcome Visitor! You can edit me in"),
            code([txt({|
  lib/components/greet.re|})]),
          ],
        ),
        p(
          ~a=[a_class(["greet__text"])],
          [
            txt(
              "Here a simple counter example that you can look at to get started:",
            ),
          ],
        ),
        div(
          ~a=[a_class(["greet__button-container"])],
          [
            button(
              ~a=[
                a_button_type(`Button),
                a_onclick(_event => inject(Action.Decrement)),
                a_class(["greet__button"]),
              ],
              [txt("-")],
            ),
            span(
              ~a=[a_class(["greet__button"])],
              [txt(Int.to_string(model))],
            ),
            button(
              ~a=[
                a_button_type(`Button),
                a_onclick(_event => inject(Action.Increment)),
                a_class(["greet__button"]),
              ],
              [txt("+")],
            ),
          ],
        ),
        div([
          span(
            ~a=[a_class(["greet__text"])],
            [
              txt("And here's a link to demonstrate navigation: "),
              Router.link(~route=Home, [txt("Home")]),
            ],
          ),
        ]),
      ],
    )
  );

let create = (model, ~old_model as _, ~inject) => {
  open Incr_dom;
  let%map.Incr model = model;
  let view = view(model, ~inject);
  Component.create(
    model,
    Tyxml.Html.toelt(view),
    ~apply_action=Action.apply(model),
  );
};
