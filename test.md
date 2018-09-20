
<p style="color: red; font-weight: bold">>>>>>  gd2md-html alert:  ERRORs: 0; WARNINGs: 0; ALERTS: 4.</p>
<ul style="color: red; font-weight: bold"><li>See top comment block for details on ERRORs and WARNINGs. <li>In the converted Markdown or HTML, search for inline alerts that start with >>>>>  gd2md-html alert:  for specific instances that need correction.</ul>

<p style="color: red; font-weight: bold">Links to alert messages:</p><a href="#gdcalert1">alert1</a>
<a href="#gdcalert2">alert2</a>
<a href="#gdcalert3">alert3</a>
<a href="#gdcalert4">alert4</a>

<p style="color: red; font-weight: bold">>>>>> PLEASE check and correct alert issues and delete this message and the inline alerts.<hr></p>



# How to use CaseView APIs in CEF Dialog

The CEF Dialog has been improved and supports most CaseView APIs and objects in WP2018 update 1. You can use CaseView APIs in HTML and JavaScript when you launch the CEF Dialog by the runHTMLDialogCef() API.


## Lanuch CEF Dialog

In CaseView, using Application. runHTMLDialogCef API to launch CEF Dialog to show the HTML file.


### Syntax


```
runHTMLDialogCef (sHTMLFileName, Flags, isModal, [dialogParam])
```



### Parameters

**sHTMLFileName** is the URL or file name of a HTML file.

**Flags** has two values 0 and 1. 1 means that the dialog is resizable.

**isModal's **type** **is bool. TRUE means that the dialog is modal dialog. FALSE means it is modeless dialog.

**dialogParam **is optional, and it is a string of JavaScript that can be passed into the HTML file.


### Return Value

This API returns string value.


### Remarks

All the CaseView APIs and Objects only can be accessed in a modal CEF dialog. It means that the **isModal **must be set TRUE when calling this API.


### Example


```
function LaunchCEFDialog() {
    // the HTML file's name
    var src = "file:///D:/test.html";
    //calling API
    Application.runHTMLDialogCef(src, 0, true);
}
```





## Debugging JavaScript in CEF Dialog

Debugging in CEF Dialog is totally different from ActiveScript or JsRT. The debugger keyword is not available in CEF Dialog. You should use DevTools to debug the JavaScript.

**Note: The JavaScript in CEF Dialog is case-sensitive and all the CV APIs (without argument) must be ended with parentheses ().**


### Turn on the DevTools

To turn on or turn off the DevTools, setting the **EnableCefDevTools** to 1 or 0 in CV.VER, by default the DevTools is hidden.


### Using DevTools to debug

There're two ways to open DevTools, one is right click in the CEF Dialog and select Show DevTools on the context menu; the other is to use Ctrl + F12.



<p id="gdcalert1" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/How-to0.png). Store image on your image server and adjust path/filename if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert2">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/How-to0.png "image_tooltip")




Click the Sources tab to show the source codes.



<p id="gdcalert2" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/How-to1.png). Store image on your image server and adjust path/filename if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert3">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/How-to1.png "image_tooltip")


The Sources panel UI has 3 parts.



<p id="gdcalert3" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/How-to2.png). Store image on your image server and adjust path/filename if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert4">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/How-to2.png "image_tooltip")




1.  The **File Navigator** pane. Every file that the page requests is listed here.
1.  The **Code Editor** pane. After selecting a file in the **File Navigator pane**, the contents of that file are displayed here.
1.  The **JavaScript Debugging** pane. Various tools for inspecting the page's JavaScript.



Set a breakpoint.

In **Code Editor** Pane, clicking the line number to set a breakpoint in the JavaScript source code. 

**Note: CEF Dialog does NOT support debugger keyword**.



<p id="gdcalert4" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/How-to3.png). Store image on your image server and adjust path/filename if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert5">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/How-to3.png "image_tooltip")


You need to reload HTML file when you open the DevTools for showing the source codes.




## The undefined method or property

If you encounter the undefined error when you call a method or property of a CV object, you should ensure that the name of the method or property is correct. You could use DevTools to check the name by following steps.



1.  Open the DevTools.
1.  Set a breakpoint on the line that calls the method of property.
1.  Active the breakpoint and move the mouse cursors to the CV object which includes the method or property.
1.  The detail window of the object will show up, the comparing the name and find the correct name.


## Date type in CEF Dialog

In CEF dialog, it doesn't support Date.getVarDate() method, since getVarDate() is supported in Internet Explorer only. You should use the JavaScript Date object instead of getVarDate().

Let's see the following sample code.


```
function SetCellDateVale()
{
     //First, get cell
    var cell = Application.Document().cell("C1"); 
   //set cell type to date type
   cell.type = 2;
   //set cell value
   cell.value = new Date('1/01/2019'); //Create Date object
}
```



## VBArray object in CEF Dialog

In CEF Dialog, the **VBArray** is not supported and you don't even have to use **VBArray**. The return type of a CaseView API which returns an Array is a JavaScript array type now. You could directly use the result as an array.

For instance: The API Document.paraIndicesByCell.


```
function paraIndices(){
    //Get the Index List
    //the return type of paraIndicesByCell is JavaScript array.
    var oParaIndexList = Document.paraIndicesByCell(sCellName);
    //iterate the array.
    for(i = 0; i < oParaIndexList.Length; i++)
    	console.log(oParaIndexList[i]);
}


<!-- GD2md-html version 1.0β11 -->
