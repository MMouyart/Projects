
/** @jsxImportSource @emotion/react */
import {Link} from '@mui/material';
import { Link as RouterLink } from 'react-router-dom';
const styles = {
  footer: {
    height: '30px',
    backgroundColor: 'rgba(51,187,255,.3)',
    flexShrink: 0
  },
}

export default function Footer() {
  return (
    <footer style={styles.footer}>
    <Link href={'https://www.ece.fr/campus-de-paris/'}>
    ECE Paris Webtech Project
    </Link>
    </footer>
  );
}
