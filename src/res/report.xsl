<?xml version="1.0" encoding="ISO-8859-15"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
  <html>
  <head>
  </head>
  <body>
    <img align="right" width="128" height="128" src="res/aslogic_trans.png"/>
    <h1>A. S. Logic Systems Co.</h1>
    <h2>Hourly Employee Report</h2>
    <table width="95%" align="center" bgcolor="#eeee99">
    <tr bgcolor="#ff0000">
        <td>Employee ID</td>
        <td>First Name</td>
        <td>Last Name</td>
        <td>Hours Worked</td>
        <td>Date</td>
    </tr>
    <xsl:for-each select="root/record">
    <tr>
        <td><xsl:value-of select="ID_Number"/></td>
        <td><xsl:value-of select="First_Name"/></td>
        <td><xsl:value-of select="Last_Name"/></td>
        <td><xsl:value-of select="Time_Worked_Hours"/>:<xsl:value-of select="Time_Worked_Minutes"/></td>
        <td><xsl:value-of select="Worked_On_Date"/></td>
    </tr>
    </xsl:for-each>
    </table>
  </body>
  </html>
</xsl:template>

</xsl:stylesheet>
