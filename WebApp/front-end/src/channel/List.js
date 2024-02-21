
/** @jsxImportSource @emotion/react */
import {forwardRef, useImperativeHandle, useLayoutEffect, useRef} from 'react'
// Layout
import { useTheme } from '@mui/styles'
// Markdown
import { unified } from 'unified'
import markdown from 'remark-parse'
import remark2rehype from 'remark-rehype'
import html from 'rehype-stringify'
import DeleteIcon from '@mui/icons-material/Delete'
import Button from '@mui/material/Button'
import Modal from '@mui/material/Modal'
import EditIcon from '@mui/icons-material/Edit'
import Box from '@mui/material/Box'
// Time
import dayjs from 'dayjs'
import calendar from 'dayjs/plugin/calendar'
import updateLocale from 'dayjs/plugin/updateLocale'
import { useNavigate} from 'react-router-dom'
import Context from '../app/Context'
import { useContext } from 'react'
import axios from 'axios'
import { useState} from 'react'

dayjs.extend(calendar)
dayjs.extend(updateLocale)
dayjs.updateLocale('en', {
  calendar: {
    sameElse: 'DD/MM/YYYY hh:mm A'
  }
})

const useStyles = (theme) => ({
  root: {
    position: 'relative',
    flex: '1 1 auto',
    overflow: 'auto',
    '& ul': {
      'margin': 0,
      'padding': 0,
      'textIndent': 0,
      'listStyleType': 0,
    },
  },
  message: {
    padding: '.2rem .5rem',
    ':hover': {
      backgroundColor: 'rgba(255,255,255,.05)',
    },
  },
  fabWrapper: {
    position: 'absolute',
    right: 0,
    top: 0,
    width: '50px',
  },
  fab: {
    position: 'fixed !important',
    top: 0,
    width: '50px',
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
  }
  })
export default forwardRef(({
  channel,
  messages,
  onScrollDown,
}, ref) => {
  const styles = useStyles(useTheme())
  // Expose the `scroll` action
  useImperativeHandle(ref, () => ({
    scroll: scroll
  }));
  const rootEl = useRef(null)
  const scrollEl = useRef(null)
  const scroll = () => {
    scrollEl.current.scrollIntoView()
  }
  // See https://dev.to/n8tb1t/tracking-scroll-position-with-react-hooks-3bbj
  const throttleTimeout = useRef(null) // react-hooks/exhaustive-deps
  useLayoutEffect( () => {
    let isMounted = true
    const rootNode = rootEl.current // react-hooks/exhaustive-deps
    const handleScroll = () => {
      if (throttleTimeout.current === null) {
        throttleTimeout.current = setTimeout(() => {
          throttleTimeout.current = null
          const {scrollTop, offsetHeight, scrollHeight} = rootNode // react-hooks/exhaustive-deps
          onScrollDown(scrollTop + offsetHeight < scrollHeight)
        }, 200)
      }
    }
    handleScroll()
    rootNode.addEventListener('scroll', handleScroll)
    return () => rootNode.removeEventListener('scroll', handleScroll)
  })
  const navigate = useNavigate()
  const {oauth} = useContext(Context)
  const [open, setOpen] = useState(false)
  const handleOpen = () => setOpen(true)
  const handleClose = () => setOpen(false)
  const [channelCopy, setChannel] = useState(channel)
  const [messageCopy, setMessage] = useState(messages)
  const handleDeleteChannel = async(channel) => {
    if(messages.length > 0){
    if(oauth.email === messages[0].author){
    try{
      await axios.delete(`http://localhost:3001/channels/${channel.id}`,{
        headers: {
          headers: {
            'Authorization': `Bearer ${oauth.access_token}`
          }
        }
      })
      window.location.reload(true)
    }catch(err)
    {
      navigate('/oups')
    }
    navigate('/channels')}}
  }
  const handleDeleteMessage = async(id) => {
    const message = messages[id]
      if(!oauth.email)
      {
        alert("no oauth")
      }
      else{
        const headers = {
        'creation':message.creation
    }}
    if(oauth.email === message.author){
      try{
         await axios.delete(`http://localhost:3001/channels/${channel.id}/messages/${message.creation}`,
            {
           headers: {
            headers: { 'Authorization': `Bearer ${oauth.access_token}`
           }
         }
         })
         window.location.reload(true)
      }

    catch(err)
    {
      navigate('/oups')
    }}
  }
    const handleModifyChannel = async() => {
      handleOpen()
    }
    const handleSubmit = async(channel) => {
    handleClose()
      /*try{
      await axios.put(`http://localhost:3001/channels/${channel.id}`,
        {
          id: channel.id,
          name: channel.name
        },
         {
        headers: {
         headers: { 'Authorization': `Bearer ${oauth.access_token}`
        }
      }
      })
      window.location.reload(true)

    }
    catch(err)
    {
      navigate('/oups')
    }
*/
    }
    const handleSubmitMessage = async() => {
      try{
      handleClose()
      //await axios.put(`http://localhost:3001/channels/${channel.id}/messages`)
      //window.location.reload(true)
    }
      catch(err)
      {
        navigate('/oups')
      }
    }
  return (
    <div css={styles.root} ref={rootEl}>

      <h1>Messages for {channel.name}

        <Button onClick={() => handleDeleteChannel(channel)}> <DeleteIcon /> Delete </Button>

        <Button onClick={() => handleModifyChannel(channel)}> <EditIcon /> Edit </Button>

          <Modal open={open} onClose={handleClose}>

            <Box sx={styles.modal}>

               <form onSubmit={() => handleSubmit(channel)}>

                 <input type="text" value={channelCopy.name}
                 onChange={(e) => setChannel(e.target.value)}/>

                 <input type="submit" value="edit" />

                </form>

             </Box>

            </Modal>

       </h1>

      <ul>
        { messages.map( (message, i) => {
            const {value} = unified()
            .use(markdown)
            .use(remark2rehype)
            .use(html)
            .processSync(message.content);
            return (
              <li key={i} css={styles.message} >
                <p>
                  <span>{message.author}</span>
                  {' - '}
                  <span>{dayjs().calendar(message.creation)}</span>
                  <Button onClick={() => handleDeleteMessage(i)}> <DeleteIcon /> Delete </Button>

                  <Button className="modal-toggle" onClick={handleOpen}> <EditIcon /> Edit </Button>

                  <Modal open={open} onClose={handleClose}>
                  <Box sx={styles.modal}>
                  <form onSubmit={handleSubmitMessage}>
                  <input type="text" value={messageCopy}
                  onChange={(e) => setMessage(e.target.value)}/>
                  <input type="submit" value="modify" />
                  </form>
                  </Box>
                  </Modal>
                </p>
                <div dangerouslySetInnerHTML={{__html: value}}>
                </div>

              </li>
            )
        })}
      </ul>
      <div ref={scrollEl} />
    </div>
  )
})
