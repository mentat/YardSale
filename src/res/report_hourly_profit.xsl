<?xml version="1.0" encoding="ISO-8859-15"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
  <html>
  <head>
  </head>
  <body>
    <img align="right" width="128" height="128" src="res/aslogic_trans.png"/>
    <h1>A. S. Logic Systems Co.</h1>
    <h2>Hourly Profit Breakdown</h2>
    <table width="95%" align="center" bgcolor="#eeee99">
    <tr bgcolor="#ff0000">
        <td>Hour</td>
        <td>Profit</td>
    </tr>
    <xsl:for-each select="root/record">
    <tr>
        <td><xsl:value-of select="Hour"/></td>
        <td><xsl:value-of select="PROFIT"/></td>
    </tr>
    </xsl:for-each>
    <tr bgcolor="#ff5500">
        <td><b>Totals:</b></td>
        <td><xsl:value-of select="sum(root/record/PROFIT)"/></td>
    </tr>
    </table>
<center><img src="res/report.png"/></center>
  </body>
  </html>
</xsl:template>

</xsl:stylesheet>
