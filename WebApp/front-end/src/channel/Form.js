
/** @jsxImportSource @emotion/react */
import axios from 'axios';
// Layout
import { Button, TextField } from '@mui/material';
import SendIcon from '@mui/icons-material/Send';
import { useTheme } from '@mui/styles';
import { useNavigate} from 'react-router-dom'
import { useContext, useState } from 'react'
import Context from '../app/Context'


const useStyles = (theme) => {
  // See https://github.com/mui-org/material-ui/blob/next/packages/material-ui/src/OutlinedInput/OutlinedInput.js
  const borderColor = theme.palette.mode === 'light' ? 'rgba(0, 0, 0, 0.23)' : 'rgba(255, 255, 255, 0.23)';
  return {
    form: {
      borderTop: `2px solid ${borderColor}`,
      padding: '.5rem',
      display: 'flex',
      backgroundColor: '#FFFFFF',
      textDecoration: 'none',
      fontSize: '16px',
      border: '2px solid #000',
      color: 'black',
    },
    content: {
      flex: '1 1 auto',
      '&.MuiTextField-root': {
        marginRight: theme.spacing(1),
      },
    },
    send: {
    },
  }
}

export default function Form({
  addMessage,
  channel,
}) {
  const {oauth} = useContext(Context)
  const [content, setContent] = useState('')
  const styles = useStyles(useTheme())
  const navigate = useNavigate()
  const onSubmit = async () => {
    try{
    if(!oauth.email){

    }
    if(oauth.email){
    if(content !== ''){
    const {data: message} = await axios.post(
      `http://localhost:3001/channels/${channel.id}/messages`
    , {
      content: content,
      author: oauth.email,
    })
    addMessage(message)
    setContent('')}
  }}catch(err)
  {
    navigate('/oups')
  }}
  const handleChange = (e) => {
    setContent(e.target.value)
  }
  return (
    <form css={styles.form} onSubmit={onSubmit} noValidate>
      <TextField
        id="outlined-multiline-flexible"
        label="Message"
        multiline
        maxRows={4}
        value={content}
        onChange={handleChange}
        variant="outlined"
        css={styles.content}
      />
      <div>
        <Button
          variant="contained"
          color="primary"
          css={styles.send}
          endIcon={<SendIcon />}
          onClick={onSubmit}
        >
          Send
        </Button>
      </div>
    </form>
  )
}
