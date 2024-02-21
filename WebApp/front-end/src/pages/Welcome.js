
/** @jsxImportSource @emotion/react */
// Layout
import { useTheme } from '@mui/styles';
import { Grid, Typography } from '@mui/material';
import { ReactComponent as ChannelIcon } from '../icons/channel.svg';
import { ReactComponent as FriendsIcon } from '../icons/friends.svg';
import { ReactComponent as SettingsIcon } from '../icons/settings.svg';
import Button from '@mui/material/Button'
import Modal from '@mui/material/Modal'
import Box from '@mui/material/Box'
import { useState} from 'react';
import axios from 'axios';
import { useNavigate} from 'react-router-dom'
import background from '../icons/background.jpeg'
const useStyles = (theme) => ({
  root: {
    height: '100%',
    flex: '1 1 auto',
    display: 'flex',
    backgroundImage: `url(${background})`,
  },
  card: {
    textAlign: 'center',
  },
  icon: {
    width: '30%',
    fill: '#fff',
  },
  modal: {
    position: 'absolute',
  top: '50%',
  left: '50%',
  transform: 'translate(-50%, -50%)',
  width: 400,
  bgcolor: 'background.paper',
  border: '2px solid #000',
  boxShadow: 24,
  p: 4
},
  button: {
    backgroundColor: '#3232FA',
    border: '2px solid #000',
    color: 'white',
    padding: '15px 32px',
    textDecoration: 'none',
    fontSize: '16px',
  }
})

export default function Welcome() {
  const styles = useStyles(useTheme())
  const [open, setOpen] = useState(false)
  const handleOpen = () => setOpen(true)
  const handleClose = () => setOpen(false)
  const [newChannel, setChannel] = useState("")
  const navigate = useNavigate()
  const handleSubmit = async() => {
    if(!newChannel){
    }
    else{
    try{
    handleClose()
     await axios.post(`http://localhost:3001/channels`, {
       name: newChannel
     })
      window.location.reload(true)
  }catch(err)
  {
    navigate('/oups')
  }
}
}
  return (
    <div css={styles.root}>
      <Grid
        container
        direction="row"
        justify="center"
        alignItems="center"
        spacing={5}
      >
        <Grid item xs>
          <div css={styles.card}>
          <Button className="modal-toggle" onClick={handleOpen} css={styles.button}>
            <ChannelIcon css={styles.icon} />
              Create channels
            </Button>
            <Typography color="textPrimary">
              <Modal open={open} onClose={handleClose}>
              <Box sx={styles.modal}>
              <form onSubmit={handleSubmit}>
              <input type="text" value={newChannel} placeholder="Create a new channel"
              onChange={(e) => setChannel(e.target.value)}/>
              <input type="submit" value="create" />
              </form>
              </Box>
              </Modal>
            </Typography>
          </div>
        </Grid>
        <Grid item xs>
          <div css={styles.card}>
          <Button css={styles.button}>
            <FriendsIcon css={styles.icon} />
            <Typography color="textPrimary">
              Invite friends
            </Typography>
            </Button>
          </div>
        </Grid>
        <Grid item xs>
          <div css={styles.card}>
          <Button css={styles.button}>
            <SettingsIcon css={styles.icon} />
            <Typography color="textPrimary">
              Settings
            </Typography>
            </Button>
          </div>
        </Grid>
      </Grid>
    </div>
  );
}
