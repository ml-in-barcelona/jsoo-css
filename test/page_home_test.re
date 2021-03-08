open Jsoo_css_demo;

let%expect_test "can render home page" = {
  let driver =
    Driver.create(
      ~initial_model=Page_home.Model.empty,
      ~initial_state=(),
      ~sexp_of_model=Page_home.Model.sexp_of_t,
      (module Page_home),
    );

  module H = (val Helpers.make(driver));
  H.show_view();
  %expect
  {|
    <div>
      <div class="greet__container">
        <p class="greet__welcome-message">
          👋 Welcome Visitor! You can edit me in
          <code>
      lib/components/greet.re </code>
        </p>
        <p class="greet__text"> Here a simple counter example that you can look at to get started: </p>
        <div class="greet__button-container">
          <button type="button" class="greet__button" onclick={handler}> - </button>
          <span class="greet__button"> 0 </span>
          <button type="button" class="greet__button" onclick={handler}> + </button>
        </div>
        <div>
          <span class="greet__text">
            And here's a link to demonstrate navigation:
            <a href="/" onclick={handler}> Home </a>
          </span>
        </div>
      </div>
    </div>
|};
  H.do_actions([Page_home.Action.Greet_action(Greet.Action.Increment)]);
  H.perform_update();
  H.show_model();
  %expect
  {| ((greet_model 1)) |};
  H.show_view();
  %expect
  {|
    <div>
      <div class="greet__container">
        <p class="greet__welcome-message">
          👋 Welcome Visitor! You can edit me in
          <code>
      lib/components/greet.re </code>
        </p>
        <p class="greet__text"> Here a simple counter example that you can look at to get started: </p>
        <div class="greet__button-container">
          <button type="button" class="greet__button" onclick={handler}> - </button>
          <span class="greet__button"> 1 </span>
          <button type="button" class="greet__button" onclick={handler}> + </button>
        </div>
        <div>
          <span class="greet__text">
            And here's a link to demonstrate navigation:
            <a href="/" onclick={handler}> Home </a>
          </span>
        </div>
      </div>
    </div>
|};
};
