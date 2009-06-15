$Id: README.txt,v 1.3.2.6 2009/05/05 11:57:08 earnie Exp $
XML Sitemap Module
Author: Matthew Loar <matthew at loar dot name>
This module was originally written as part of Google Summer of Code 2005.

DESCRIPTION
-----------
The XML sitemap module creates a sitemap report conforming to the sitemaps.org
specification. It provides many options for customizing the data reported in the
sitemap.

INSTALLATION AND UPGRADING
--------------------------
See INSTALL.txt in this directory.

KNOWN ISSUES
------------
Users who have not enabled clean URLs have reported receiving an
"Unsupported file format" error from Google. The solution is to replace
"?q=sitemap.xml" at the end of the submission URL with
"index.php?q=sitemap.xml", or to enable the clean URLs.
Submission URLs for each search engine can be
configured at http://www.example.com/?q=admin/settings/xmlsitemap/engines.

MORE INFORMATION
----------------
The sitemap protocol: http://sitemaps.org.

SEARCH ENGINES
--------------
Ask - http://submissions.ask.com/ping
Google - http://www.google.com/webmasters/sitemap
Moreover - http://w.moreover.com/public/products/search_engine_toolkit.html
Windows Live - http://webmaster.live.com/
Yahoo! - http://developer.yahoo.com/search/siteexplorer/V1/ping.html
