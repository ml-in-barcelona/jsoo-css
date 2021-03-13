module App = {
  [@react.component]
  let make = () => {
    <div className="App">
      <h1> {React.string("Hello CodeSandbox")} </h1>
      <h2> {React.string("Start editing to see some magic happen!")} </h2>
    </div>;
  };
};

React.Dom.renderToElementWithId(<App />, "root");
