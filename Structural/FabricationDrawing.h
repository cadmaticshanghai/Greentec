/* deinfe tag for model group*/
#define	Tag_DrawingName             "U76"       /*舾装件制造图图名*/

/* define drawing tag name */ 
#define	Tag_Drawing_ShipNumber      "~D1"      /* 船号 */
#define	Tag_Drawing_DrawingNumber   "~D2"      /* 图号 */
#define	Tag_Drawing_PageNumber      "~D3"      /* 页码 */
#define	Tag_Drawing_TotalPage       "~D4"      /* 总页数 */
#define	Tag_Drawing_ModuleName      "~G6"      /* 模型名 */
#define	Tag_Drawing_UnitName        "G04"      /* 舾装件名称 */

/*尺寸标注设置*/
global int			DimLinePen = 1;
global string		DimLineWidthName = "0.25";
global int			DimLineColor = 1;
global string		DimLineColorName = "red";
global int			DimLineLayer = 104;
global string		DimLineLayerName = "PM_dim_layer";
global float		DimTextHeight = 2.5;
global float		DimTextWidth = 1.5;
global float		DimTextSpc = 0.5;
global float		DimSymHeight = 2.0;

/*define tag of drawing*/
#define  Tag_DrawingStatus   "U39"
#define  Tag_CreationTime    ".c6"

/* define view position*/
global int	View1_X = 85, View1_Y = 200;
global int 	View2_X = 200,View2_Y = 200;
global int 	View3_X = 85, View3_Y = 77;
global int 	View4_X = 320,View4_Y = 200;

/*define view size*/
global float	View_Size  = 150;
global float	View_Scale = 50;
global handle View_Info,View_Handles,View_Names,View_Positions;


/*define ISO view direction*/
global float AxoRotAngle=-120.0;
global float AxoSlopeAngle=30.0;


global int Text_Colour = 1;
global int Text_Height = 3;

global   int      Group_Type_I = 7;

/* 零件标注相关系统变量 */
#define	Lbl_Name_Part_No	"Part_no_ref"

/*保存管段零件表内容的全局数组*/
global handle Mto_Table;
global handle Mto_Label_Table;
global int Mto_Number = 0;

/*零件表相关设置*/
global int Mto_Table_Orign_X = 213.25;
global int Mto_Table_Orign_Y = 16.93;
global int Mto_Table_W = 200.3;
global int Mto_Table_H = 4.73;
global int Mto_Table_Column1_W = 15.97;
global int Mto_Table_Column2_W = 64.77;
global int Mto_Table_Column3_W = 19.92;
global int Mto_Table_Column4_W = 29.91;
global int Mto_Table_Column5_W = 22.42;
global int Mto_Table_Column6_W = 22.44;
global int Mto_Table_Column7_W = 24.9;
global string Mto_Table_Direction = "Up"; /* Down - 从上向下 Up - 从下向上*/
global int Mto_Table_Line_Type = 0;
global int Mto_Table_Line_Colour = 1;
global int Mto_Table_Pattern_Length = 0;
global int Mto_Table_Text_Colour = 2;
global int Mto_Table_Text_Height = 2.5;

global int Max_Parts_Number = 500;


set_column_title(handle wobj, column_titles, column_number)
{
	for (i = 0; i < column_number; i = i + 1;)
	{
		title = A_GET(column_titles,i);
		if (ISSTRING(title))
		{
			W_SET_WINDOW_ARGS(wobj, W_LISTW_COLUMN, i, W_LISTW_HEADER, title);
			W_SET_WINDOW_ARGS(wobj, W_LISTW_COLUMN, i, W_LISTW_COLUMNWIDTH,-1);
			W_SET_WINDOW_ARGS(wobj, W_LISTW_COLUMN, i, W_LISTW_ITEMTYPE, W_LISTW_STRING_COLUMN); 
		}
		else 
		{
			return(0);
		}
	}
	return(0);
}