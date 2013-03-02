<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="html" version="4.0" encoding="utf-8" indent="no" omit-xml-declaration="yes"
  />

<xsl:variable name="noc">
  <xsl:value-of select="count(/kinf/members/member) + 1"/>
</xsl:variable>

<xsl:template match="kinf">
  <html>
    <head>
      <meta charset="utf-8"/>
      <meta http-equiv="X-UA-Compatible" content="chrome=1"/>
  
      <link rel="stylesheet" href="stylesheets/styles.css"/>
      <link rel="stylesheet" href="stylesheets/pygment_trac.css"/>
      <meta name="viewport" content="width=device-width, initial-scale=1, user-scalable=no"/>
      <title>
        KInf Hall of Fame
      </title>
      <!--[if lt IE 9]>
      <script src="//html5shiv.googlecode.com/svn/trunk/html5.js"></script>
      <![endif]-->
    </head>
    <body>
      <div class="wrapper">
        <header>
          <h1>KInf Hall of Fame</h1>

          <a href="https://github.com/anagorko/kinf/wiki/">Wróć na stronę</a>

          <br/><br/>
          <h2>Legenda</h2>
          
          <table>
            <tr>
              <td><img src="images/good.png"/></td>
              <td>zadanie zaliczone.</td>
            </tr>
            <tr>
              <td><img src="images/wrong.png"/></td>
              <td>zadanie rozpoczęte lub rozwiązane z błędami.</td>
            </tr>
            <tr>
              <td>&#160;</td>
              <td>zadanie nierozpoczęte.</td>
            </tr>
          </table>
          
        </header>
        <section>
          <xsl:apply-templates select="member-group"/>
        </section>
        <footer>
          &#169; 2013 <a href="https://github.com/anagorko/kinf">Kółko 
          Informatyczne</a>&#160;<a href="http://zagle.sternik.edu.pl">Szkoły Żagle</a>.
        </footer>
      </div>
      <script src="javascripts/scale.fix.js"></script>
    </body>
  </html>
</xsl:template>

<xsl:template match="member-group">
  <h1><xsl:value-of select="title"/></h1>
  <br clear="both"/><br/>
  <table style="margin-top: 20px">
    <tr>
      <td></td>
      <xsl:apply-templates select="members/member"/>
    </tr>
    <xsl:apply-templates select="problems/problem-group">
      <xsl:with-param name="nom" select="count(members/member) + 1"/>
    </xsl:apply-templates>
  </table>
  <br/>
</xsl:template>

<xsl:template match="member">
  <td style="width: 16px">
    <div style="overflow: visible; width: 16px">
      <div>
        <xsl:attribute name="style">
          color: #400000;
          
          -webkit-transform: rotate(-90deg);
    /* Firefox */
    -moz-transform: rotate(-90deg);
    
    /* IE */
    -ms-transform: rotate(-90deg);
    
    /* Opera */
    -o-transform: rotate(-90deg);
        </xsl:attribute>
        <xsl:value-of select="@id"/>
      </div>
    </div>
  </td>
</xsl:template>

<xsl:template match="problem-group">
  <xsl:param name="nom"/>
  <tr>
    <th style="font-weight:bold">
      <xsl:attribute name="colspan">
        <xsl:value-of select="$nom"/>
      </xsl:attribute>
      <xsl:value-of select="title"/>
    </th>
  </tr>
  <xsl:apply-templates select="problem"/>
</xsl:template>

<xsl:template match="problem">
  <tr>
    <td style="white-space: nowrap">
      <xsl:attribute name="title"><xsl:value-of select="@id"/></xsl:attribute>
      <xsl:value-of select="name"/>
    </td>
    <xsl:apply-templates select="../../../members/member" mode="problem-solved">
      <xsl:with-param name="problem_id"><xsl:value-of select="@id"/></xsl:with-param>
    </xsl:apply-templates>
  </tr>
</xsl:template>

<xsl:template match="member" mode="problem-solved">
  <xsl:param name="problem_id"/>
  <xsl:variable name="member_id"><xsl:value-of select="@id"/></xsl:variable>
  <td style="border-left: 1px solid #cccccc">
    <xsl:if test="/kinf/member-group/solutions/problem-solved[@id=$problem_id]/solution[@who=$member_id]">
      <xsl:choose>
        <xsl:when test="/kinf/member-group/solutions/problem-solved[@id=$problem_id]/solution[@who=$member_id]/@accepted">
          <img src="images/good.png">
            <xsl:attribute name="title">
              <xsl:value-of select="$member_id"/>/<xsl:value-of select="$problem_id"/>
            </xsl:attribute>
          </img>
        </xsl:when>
        <xsl:otherwise>
          <img src="images/wrong.png">
            <xsl:attribute name="title">
              <xsl:value-of select="$member_id"/>/<xsl:value-of select="$problem_id"/>
            </xsl:attribute>
          </img>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:if>
  </td>
</xsl:template>

</xsl:stylesheet>
