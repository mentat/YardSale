<?xml version="1.0" encoding="ISO-8859-15"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
  <html>
  <head>
  </head>
  <body>
    <img align="right" width="128" height="128" src="res/aslogic_trans.png"/>
    <h1>A. S. Logic Systems Co.</h1>
    <h2>Employee Sales Report</h2>
    <table width="95%" align="center" bgcolor="#eeee99">
    <tr bgcolor="#ff0000">
        <td>Employee ID</td>
        <td>First Name</td>
        <td>Last Name</td>
        <td>Profit</td>
        <td>Retail Total</td>
        <td>Total Wholesale Cost</td>
    </tr>
    <xsl:for-each select="root/record">
    <tr>
        <td><xsl:value-of select="Employee_ID"/></td>
        <td><xsl:value-of select="First_Name"/></td>
        <td><xsl:value-of select="Last_Name"/></td>
        <td><xsl:value-of select="PROFIT"/></td>
        <td><xsl:value-of select="RETAIL_TOTAL"/></td>
        <td><xsl:value-of select="TOTAL_WHOLESALE_COST"/></td>
    </tr>
    </xsl:for-each>
    <tr bgcolor="#ff5500">
        <td></td>
        <td></td>
        <td><b>Totals:</b></td>
        <td><xsl:value-of select="sum(root/record/PROFIT)"/></td>
        <td><xsl:value-of select="sum(root/record/RETAIL_TOTAL)"/></td>
        <td><xsl:value-of select="sum(root/record/TOTAL_WHOLESALE_COST)"/></td>
    </tr>
    </table>
  </body>
  </html>
</xsl:template>

</xsl:stylesheet>
