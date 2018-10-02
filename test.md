
# How to use CaseView APIs in the CEF dialog

The CEF dialog has been improved and supports most CaseView APIs and objects in WP2018 Update 1. You can use CaseView's APIs in HTML and JavaScript on the CEF Dialog.


## Opening the CEF dialog

In CaseView, use Application. runHTMLDialogCef() API to launch the CEF dialog.


### Syntax


```
runHTMLDialogCef (sHTMLFileName, Flags, isModal, [dialogParam])
```



### Parameters

**sHTMLFileName** - the URL or HTML filename.

**Flags** - two possible values, 0 and 1. 1 indicates that the dialog is resizable.

**isModal's **-** **type** **is bool. TRUE indicates the dialog is modal. FALSE indicates a non-modal dialog.

**dialogParam **-** **optional. A JavaScript string that can be passed to the HTML file.


### Return Value

Returns a string.


### Notes

CaseView APIs and objects can only be accessed in a modal CEF dialog.


### Example


```
function LaunchCEFDialog() {
    // the HTML file's name
    var src = "file:///D:/test.html";
    //calling API
    Application.runHTMLDialogCef(src, 0, true);
}
```





## Debugging JavaScript in the CEF dialog

Debugging the CEF dialog is totally different from ActiveScript or JsRT. Use DevTools when debugging.


### Enablging DevTools

To enable DevTools, set **EnableCefDevTools** to 1 in CV.VER. By default, DevTools is hidden, i.e. set to 0.


### Using DevTools to debug

Right click in the CEF dialog and click **Show DevTools **on the context menu to open DevTools.

<p id="gdcalert1" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/How-to0.png). Store image on your image server and adjust path/filename if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert2">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/How-to0.png "image_tooltip")




Click the **Sources **tab to show the source codes.



<p id="gdcalert2" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/How-to1.png). Store image on your image server and adjust path/filename if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert3">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/How-to1.png "image_tooltip")


The Sources UI has 3 parts:



<p id="gdcalert3" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/How-to2.png). Store image on your image server and adjust path/filename if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert4">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/How-to2.png "image_tooltip")




1.  The **File Navigator** pane. Every file that the page requests is listed here.
1.  The **Code Editor** pane. After selecting a file in the **File Navigator pane**, the content of the file isdisplayed here.
1.  The **JavaScript Debugging** pane. Various tools for inspecting a page's JavaScript.



Setting a breakpoint.

In the **Code Editor** pane, clicking the line number will set a breakpoint in the JavaScript source code. 

**Note: The debugger keyword only works when DevTools is opened**.



<p id="gdcalert4" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/How-to3.png). Store image on your image server and adjust path/filename if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert5">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/How-to3.png "image_tooltip")


You need to reload the HTML file when you open DevTools in order to show the source code.




## Undefined method or property

If you encounter an undefined error when you call a method or property of a CV object, ensure that the name of the method or property is correct. You can use DevTools to verify the name as follows:



1.  Open DevTools.
1.  Set a breakpoint on the line that calls the method or property.
1.  Activate the breakpoint and move the mouse cursor to the CV object which includes the method or property.
1.  The Detail window of the object will display..


## Date type in the CEF dialog

The CEF dialog does not support the **Date.getVarDate()** method because getVarDate() is supported in Internet Explorer only. Use the JavaScript Date object instead.

Example:


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



## VBArray object in the CEF dialog

The CEF dialog does not support **VBArray** and is also not required. The return type of a CaseView API returning an Array is a JavaScript array. The result can be used as an array.

Example: Document.paraIndicesByCell.


```
function paraIndices(){
    //Get the Index List
    //the return type of paraIndicesByCell is JavaScript array.
    var oParaIndexList = Document.paraIndicesByCell(sCellName);
    //iterate the array.
    for(i = 0; i < oParaIndexList.Length; i++)
    	console.log(oParaIndexList[i]);
}
```



## ActiveXObject in the CEF dialog

The ActiveX object has been deprecated in the CEF dialog but you can use the Application.addActiveXObj API to add a WP ActiveX object into an HTML file.

** **


## Important Notes



*   **JavaScript in the CEF dialog is case-sensitive and all CV APIs (without argument) must end with parentheses ().**
*   **Some CV APIS that can pop up a window, like doc.MessageBox, will block the script meaning that the JavaScript will stop running and will wait for a response. This will cause the CV API execution timeout if there is no response for a long period of time (more than 500 seconds).  Avoid using this kind of API and use HTML code instead. You could use JavaScript alert or confirm instead of MessageBox, or using HTML and CSS, create a message box.**


