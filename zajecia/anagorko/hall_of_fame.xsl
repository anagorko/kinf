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

          <p class="view"><a href="https://github.com/anagorko/kinf">View the Project on GitHub <small>anagorko/kinf</small></a></p>

        </header>
        <section>
          <br clear="both"/>
          <table style="margin-top: 20px">
            <tr>
              <td></td>
              <xsl:apply-templates select="members/member"/>
            </tr>
            <xsl:apply-templates select="problems/problem-group"/>
          </table>
        </section>
        <footer>
          <p>This project is maintained by <a href="https://github.com/anagorko">anagorko</a></p>
          <p><small>Hosted on GitHub Pages - Theme by <a href="https://github.com/orderedlist">orderedlist</a></small></p>
        </footer>
      </div>
      <script src="javascripts/scale.fix.js"></script>
    </body>
  </html>
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
  <tr>
    <th style="font-weight:bold">
      <xsl:attribute name="colspan">
        <xsl:value-of select="$noc"/>
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
    <xsl:apply-templates select="//members/member" mode="problem-solved">
      <xsl:with-param name="problem_id"><xsl:value-of select="@id"/></xsl:with-param>
    </xsl:apply-templates>
  </tr>
</xsl:template>

<xsl:template match="member" mode="problem-solved">
  <xsl:param name="problem_id"/>
  <xsl:variable name="member_id"><xsl:value-of select="@id"/></xsl:variable>
  <td style="border-left: 1px solid #cccccc">
    <xsl:if test="/kinf/solutions/problem-solved[@id=$problem_id]/solution[@who=$member_id]">
      <xsl:choose>
        <xsl:when test="/kinf/solutions/problem-solved[@id=$problem_id]/solution[@who=$member_id]/@accepted">
          <img src="images/checkmark.png">
            <xsl:attribute name="title">
              <xsl:value-of select="$member_id"/>/<xsl:value-of select="$problem_id"/>
            </xsl:attribute>
          </img>
        </xsl:when>
        <xsl:otherwise>
          <img src="images/pause.png">
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
