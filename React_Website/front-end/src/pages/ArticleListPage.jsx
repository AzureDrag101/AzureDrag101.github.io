import {Link} from "react-router-dom";
import articles from "../article-content";
import ArticlesList from "../ArticlesList";

export default function ArticleListPage() {
    return (
        <>
        <h1>Articles</h1>
        <ArticlesList articles={articles}/>
        </>
    );
}