import React from 'react';
import ReactDOM from 'react-dom';
import { CookiesProvider } from 'react-cookie';
import './index.css';
import App from './app/App';
import { Provider as ContextProvider } from './app/Context';
import * as serviceWorker from './other/serviceWorker';
import 'typeface-roboto'
// Layout
import { createTheme, ThemeProvider } from '@mui/material/styles';
import {
  BrowserRouter as Router,
} from "react-router-dom";

const theme = createTheme({
  palette: {
    mode: 'dark',
  }
});

ReactDOM.render(
  <React.StrictMode>
    <ContextProvider>
      <CookiesProvider>
        <ThemeProvider theme={theme}>
          <Router>
            <App />
          </Router>
        </ThemeProvider>
      </CookiesProvider>
    </ContextProvider>
  </React.StrictMode>,
  document.getElementById('root')
);

// If you want your app to work offline and load faster, you can change
// unregister() to register() below. Note this comes with some pitfalls.
// Learn more about service workers: https://bit.ly/CRA-PWA
serviceWorker.unregister();
