
/** @jsxImportSource @emotion/react */
import { useContext } from 'react';
import axios from 'axios';
// Layout
import { useTheme } from '@mui/styles';
import { IconButton, Link } from '@mui/material';
import MenuIcon from '@mui/icons-material/Menu';
import Context from '../app/Context';
import {useNavigate} from 'react-router-dom'
import LogoutIcon from '@mui/icons-material/Logout'
import Button from '@mui/material/Button'
const useStyles = (theme) => ({
  header: {
    padding: theme.spacing(1),
    backgroundColor: '#3232FA',
    flexShrink: 0,
  },
  headerLogIn: {
    backgroundColor: 'red',
  },
  headerLogOut: {
    backgroundColor: 'blue',
  },
  menu: {
    [theme.breakpoints.up('sm')]: {
      display: 'none !important',
    },
  },
  button: {
    backgroundColor: '#FFFFFF',
    border: '2px solid #000',
    color: 'black',
    padding: '7px 16px',
    textDecoration: 'none',
    fontSize: '16px',
  }
})


export default function Header({
  drawerToggleListener
}) {
  const styles = useStyles(useTheme())
  const {
    oauth, setOauth,
    drawerVisible, setDrawerVisible
  } = useContext(Context)
  const drawerToggle = (e) => {
    setDrawerVisible(!drawerVisible)
  }
  const onClickLogout = (e) => {
    e.stopPropagation()
    setOauth(null)
  }
  return (
    <header css={styles.header}>
      <IconButton
        color="inherit"
        aria-label="open drawer"
        onClick={drawerToggle}
        css={styles.menu}
      >
        <MenuIcon />
      </IconButton>

      {
        oauth ?
        <div>
          <span>
            <p>Welcome {oauth.email}</p>
            </span>
            <Button onClick={onClickLogout} css={styles.button}>  <LogoutIcon />Logout</Button>
          </div>
        :
        <span> </span>

      }

    </header>
  );
}
