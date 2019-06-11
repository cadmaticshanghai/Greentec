/*define tag of model group*/
#define	UnitDescription         "~G6"       /* 舾装件单元的描述 */
#define	PlanningUnit            "~G2"       /* 舾装件所属托盘 */
#define	SurfaceTreatment        "U68"       /* 舾装件表面处理 */
#define	DrawingName             "U66"       /* 舾装件制造图图名 */
#define	DrawingNo               "U58"       /* 舾装件制造图图号 */
#define	BlockName               ".m1"       /* 舾装件所属分段 */
#define	UnitMaterial            "!04"       /* 舾装件材料 */

/* define drawing tag name */ 
#define	Tag_Drawing_ShipNumber       "~D1"      /* 船号 */
#define	Tag_Drawing_DrawingNumber    "~D2"      /* 图号 */
#define	Tag_Drawing_PageNumber       "~D3"      /* 页码 */
#define	Tag_Drawing_TotalPage        "~D4"      /* 总页数 */

/*尺寸标注设置*/
global int		DimLinePen = 1;
global string		DimLineWidthName = "0.25";
global int		DimLineColor = 1;
global string		DimLineColorName = "red";
global int		DimLineLayer = 104;
global string		DimLineLayerName = "PM_dim_layer";
global float		DimTextHeight = 2.5;
global float		DimTextWidth = 1.5;
global float		DimTextSpc = 0.5;
global float		DimSymHeight = 2.0;

/*define tag of drawing*/
#define  DrawingStatus   "U39"
#define  CreationTime    ".c6"

/* define view position*/
global int	View1_X = 85, View1_Y = 210;
global int 	View2_X = 200,View2_Y = 210;
global int 	View3_X = 85, View3_Y = 77;
global int 	View4_X = 320,View4_Y = 210;

/*define view size*/
global float	View_Size  = 120;
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

remove_module_name(seat_no)
{
   name = STRINGTERM(seat_no,"-");
   no = SEARCH(seat_no,"-");
   length = STRLEN(name);
   if(length > 2){
      name = TAIL(name,2);
      seat_no = name + no;
   } 
}