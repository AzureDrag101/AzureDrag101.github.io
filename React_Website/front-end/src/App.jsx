import{
  createBrowserRouter,
  RouterProvider,
} from 'react-router-dom'

import './App.css'
import HomePage from './pages/HomePage'
import AboutPage from './pages/AboutPage'
import ArticleList from './pages/ArticleListPage'
import ArticlePage from './pages/ArticlePage'
import ArticleListPage from './pages/ArticleListPage'
import Layout from './Layout'
import NotFoundPage from './pages/NotFoundPage'
import { Children } from 'react'


const routes = [{
  path:'/',
  element: <Layout/>,
  errorElement: <NotFoundPage/>,
  children:[{
    path: '/',
    element: <HomePage/>
  }, {
    path: '/about',
    element: <AboutPage/>
  }, {
    path: '/articles',
    element: <ArticleListPage/>
  }, {
    path: '/articles/:name', // -> /article/learn-react
    element: <ArticlePage/>
  }   ]
}]




const router = createBrowserRouter(routes);


function App() {

  return (
    <RouterProvider router={router}/>
  );
}

export default App
