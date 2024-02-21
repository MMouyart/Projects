/** @jsxImportSource @emotion/react */
import {useContext, useEffect} from 'react';
import axios from 'axios';
// Layout
import {Link} from '@mui/material';
import { Link as RouterLink } from 'react-router-dom';
// Local
import Context from '../app/Context'
import {useNavigate} from 'react-router-dom'
import HomeIcon from '@mui/icons-material/Home'
import Button from '@mui/material/Button'
const styles = {
  root: {
    '& a': {
      padding: '.2rem .5rem',
      whiteSpace: 'nowrap'
    }
  },
  channel: {
    backgroundColor: 'white',
    padding: '7px 16px',
    textDecoration: 'none',
    fontSize: '16px',
    border: '2px solid #000',
    color: '#3232FA',
  }
}

export default function Channels() {
  const {
    oauth,
    channels, setChannels
  } = useContext(Context)
  const navigate = useNavigate();
  useEffect( () => {
    const fetch = async () => {
      try{
        const {data: channels} = await axios.get('http://localhost:3001/channels', {
          headers: {
            'Authorization': `Bearer ${oauth.access_token}`
          }
        })
        setChannels(channels)
      }catch(err){
        console.error(err)
      }
    }
    fetch()
  }, [oauth, setChannels])

  return (
    <ul css={styles.root}>
      <li css={styles.channel}>
        <Button to="/channels" component={RouterLink} css={styles.button}>
        <HomeIcon /> Welcome</Button>
      </li>
      { channels.map( (channel, i) => (
        <li key={i} css={styles.channel}>
          <Link
            href={`/channels/${channel.id}`}
            onClick={ (e) => {
              e.preventDefault()
              navigate(`/channels/${channel.id}`)
            }}

          >
            {channel.name}
          </Link>
        </li>
      ))}
    </ul>
  );
}
