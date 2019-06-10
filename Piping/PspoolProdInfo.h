/*Define system tag - 定义系统相关属性*/
#define	Tag_System_SurfTreatIn      "~S1"                       /*1. 系统内表面处理 */
#define	Tag_System_SurfTreatOut     "~S2"                       /*2. 系统外表面处理 */
#define	Tag_System_TestPressure     "~S3"                       /*3. 系统试验压力   */

/*Define spool tag - 定义管段相关属性*/
#define	Tag_Spool_Name              "PSA"                          /*1.管段名称*/
#define	Tag_Spool_SurfTreatmentIn   "PS3"                          /*2.管子内表面处理*/
#define	Tag_Spool_SurfTreatmentOut  "PS4"                          /*3.管子外表面处理*/
#define	Tag_Spool_Type              "PS7"                          /*4.管段类型*/
#define	Tag_Spool_TestPressure      "PS5"                          /*5.管段试验压力*/
#define	Tag_Spool_Weight            "PS6"                          /*6.管段重量*/
#define	Tag_Spool_Page              "PS8"                          /*7.小票页码*/
#define	Tag_Spool_TotalPage         "PS9"                          /*8.总页数*/
#define	Tag_Spool_DrawingNumber     "PS2"                          /*9.图号*/

global int  Debug = 1;

/*
Input parameter
No.       Name           Type          Description
1.        object_handle  handle        handle of pipe spool
2.        tag_array      Array         array of pipe spool data tag 
3.        tag_number     int           number of tag
############返回值##########################################
按照参数PDM_Tag_Array中的属性定义返回对应的值   
############################################################    
*/
Get_Production_Data(object_handle, tag_array, tag_number)
{
    /*获取管段中所有的pipe及standard component*/
	parts = PM_GET_OBJECTS_IN_GROUP(object_handle);
	part_number = PM_NR_MEMBERS_IN_SET(parts);
	find = 0;
	sequence = 0;
	while(!find){
		part = PM_GET_MEMBER_IN_SET(parts,sequence);
		part_type = PM_GET_OBJDATA(part,0,MMT_TAG_OBJTYPE);
		if(part_type == "2" | part_type == "3"){
			find=1;
		}
		sequence = sequence + 1;
	}
	/*定义保存管段信息的一维数组*/
	production_data = A_ALLOC(tag_number);
	/*遍历管段的属性名数组并根据属性名返回对应的值*/
	for (i = 0; i < tag_number; i = i + 1;){
	    /*获取属性名*/
		att = A_GET(tag_array,i);
		/*根据属性名抽取对应的属性值*/
		if(att == MMT_TAG_SYSTEM_NAME){
			data = PM_GET_OBJDATA(part,0,MMT_TAG_SYSTEM_NAME);
		}
		else if(att == MMT_TAG_PIPELINE_NAME){
			data = PM_GET_OBJDATA(part,0,MMT_TAG_PIPELINE_NAME);
		}
		else{
			data = Get_Attribute_Value(object_handle,att);
		}
		
		if (ISSTRING(data) & data != ""){
			A_PUT(production_data,i,data);
		}
		/*如果抽取不到对应的属性值，则计算或者抽取这个属性的默认值*/
		else 
		{
			data = get_def_data(object_handle, att);
			A_PUT(production_data,i,data);
		}
	}
	return(production_data);
}

/*
**check if tag already exit
*/
Validate_Attribute(tag,tag_description)
{
	attr_h = PM_FIND_ATTRIBUTE(tag);
	if (attr_h == 0) {
		message = "属性<" + tag_description + ">未定义。";
		st = U_MESSAGE(message);
		return(-1);
	}
	return(0);
}

/*
#############功能说明FunctionDescription####################
获取指定管段对象的默认生产信息
Get PDM data of the indicated pipe spool
#############参数说明#######################################
序号      名称           类型          说明
1.        object_handle  handle        模型对象的句柄handle of model
2.        PDM_Tag_Array  Array         模型生产信息属性数组array storing the PDM data of model
3.        PDM_Number     int           生产信息数量number of PDM data
############返回值##########################################
按照参数PDM_Tag_Array中的属性定义返回对应的默认值   
############################################################    
*/
get_def_production_data( object_handle, tag_array, tag_number)
{
	parts = PM_GET_OBJECTS_IN_GROUP(object_handle);
	part_number = PM_NR_MEMBERS_IN_SET(parts);
	find = 0;
	sequence = 0;
	while(!find){
		part = PM_GET_MEMBER_IN_SET(parts,sequence);
		part_type = PM_GET_OBJDATA(part,0,MMT_TAG_OBJTYPE);
		if(part_type == "2" | part_type == "3"){
			find=1;
		}
		sequence = sequence + 1;
	}
	production_data = A_ALLOC(tag_number);
	for (i = 0; i < tag_number; i = i + 1;){
		att = A_GET(tag_array,i);
		data = get_def_data(object_handle, att);
		A_PUT(production_data,i,data);
	}
	return(production_data);
}

/*
**set pipe spool default production data, this is used for new pipe spool
*/
Set_Def_Production_Data( object_handle, tag_array, tag_number)
{
	access = CheckAccessRight(object_handle);
	production_data = get_def_production_data( object_handle, tag_array, tag_number);
	for (i = 0; i < tag_number; i = i + 1){
		tag = A_GET(tag_array,i);
		if(tag != MMT_TAG_PIPELINE_NAME & tag != MMT_TAG_SYSTEM_NAME){
			if(access){
				attribute_value = A_GET(production_data, i);
				Set_Attribute_Value( object_handle, tag, attribute_value);
			}				
		}
	}	
	return(0);
}

get_def_data(handle object_handle, string tag)
{	
	access = CheckAccessRight(object_handle);
	if ( tag == Tag_Spool_Name ){
		data = get_def_spool_name(object_handle);
		if(access){
			Set_Attribute_Value(object_handle, tag, data);
		}
		return(data);
	}		
	else if ( tag == Tag_Spool_SurfTreatmentIn  ){
		data = get_def_tube_inside_surface_treatment(object_handle);
		if(access){
			Set_Attribute_Value(object_handle, tag, data);
		}
		return(data);
	}	
	else if ( tag == Tag_Spool_SurfTreatmentOut  ){
		data = get_def_tube_outside_surface_treatment(object_handle);
		if(access){
			Set_Attribute_Value(object_handle, tag, data);
		}
		return(data);
	}
	else if ( tag == Tag_Spool_TestPressure ){
		data = get_def_pressure_test(object_handle);
		if(access){
			Set_Attribute_Value(object_handle, tag, data);
		}
		return(data);
	}		
	else if ( tag == Tag_Spool_Type ){
		data = get_def_spool_type(object_handle);
		if(access){
			Set_Attribute_Value(object_handle, tag, data);
		}
		return(data);
	}	
	else if ( tag == Tag_Spool_Weight ){
		data = FTOASCII(Get_Pipe_Spool_Weight(object_handle));
		if(access){
			Set_Attribute_Value(object_handle, tag, data);
		}
		return(data);
	}
	else if ( tag == Tag_Spool_Page ){
		data = "0";
		if(access){
			Set_Attribute_Value(object_handle, tag, data);
		}
		return(data);
	}
	else if ( tag == Tag_Spool_TotalPage ){
		data = "0";
		if(access){
			Set_Attribute_Value(object_handle, tag, data);
		}
		return(data);
	}
	else if ( tag == Tag_Spool_DrawingNumber ){
		data = "DrawingNo";
		if(access){
			Set_Attribute_Value(object_handle, tag, data);
		}
		return(data);
	}
	else if ( tag == MMT_TAG_SYSTEM_NAME ){
		data = Get_Def_Spool_System_Name(object_handle);
		return(data);
	}
	else if ( tag == MMT_TAG_PIPELINE_NAME ){
		data = Get_Def_Spool_PipeLine_Name(object_handle);
		return(data);
	}
}


Get_Def_Spool_System_Name(handle object_handle)
{
    /* 获取管段零件所属的系统名称 */
	parts = PM_GET_OBJECTS_IN_GROUP(object_handle);
	part_number = PM_NR_MEMBERS_IN_SET(parts);
	find = 0;
	sequence = 0;
	while(!find){
		part = PM_GET_MEMBER_IN_SET(parts,sequence);
		part_type = PM_GET_OBJDATA(part,0,MMT_TAG_OBJTYPE);
		if(part_type == "2" | part_type == "3"){
			find=1;
		}
		sequence = sequence + 1;
	}
    system_name = PM_GET_OBJDATA(part,0,MMT_TAG_SYSTEM_NAME);
	if(ISSTRING(system_name)){
	   return(system_name);
	} 
	return("未定义");
}


Get_Def_Spool_PipeLine_Name(handle object_handle)
{
    /* 获取管段零件所属的系统名称 */
	parts = PM_GET_OBJECTS_IN_GROUP(object_handle);
	part_number = PM_NR_MEMBERS_IN_SET(parts);
	find = 0;
	sequence = 0;
	while(!find){
		part = PM_GET_MEMBER_IN_SET(parts,sequence);
		part_type = PM_GET_OBJDATA(part,0,MMT_TAG_OBJTYPE);
		if(part_type == "2" | part_type == "3"){
			find=1;
		}
		sequence = sequence + 1;
	}
    pipeline_name = PM_GET_OBJDATA(part,0,MMT_TAG_PIPELINE_NAME);
	if(ISSTRING(pipeline_name)){
	   return(pipeline_name);
	} 
	return("未定义");
}

get_def_tube_inside_surface_treatment(handle object_handle)
{
   /*抽取管段所属管线的表面处理定义，如果没有设置，则继续抽取管段所属系统的表面处理定义*/
	parts = PM_GET_OBJECTS_IN_GROUP(object_handle);
	part_number = PM_NR_MEMBERS_IN_SET(parts);
	find = 0;
	sequence = 0;
	while(!find){
		part = PM_GET_MEMBER_IN_SET(parts,sequence);
		part_type = PM_GET_OBJDATA(part,0,MMT_TAG_OBJTYPE);
		if(part_type == "2" | part_type == "3"){
			find=1;
		}
		sequence = sequence + 1;
	}
		
   /*抽取管段所属系统的表面处理定义，如果没有设置，则默认为镀锌*/
	surface_treatment = PM_GET_OBJDATA(part,0,Tag_System_SurfTreatIn);
	if(ISSTRING(surface_treatment)){
	   return(surface_treatment);
	} 
	else{
	    return("镀锌");
	}
}

get_def_tube_outside_surface_treatment(handle object_handle)
{
   /*抽取管段所属管线的表面处理定义，如果没有设置，则继续抽取管段所属系统的表面处理定义*/
	parts = PM_GET_OBJECTS_IN_GROUP(object_handle);
	part_number = PM_NR_MEMBERS_IN_SET(parts);
	find = 0;
	sequence = 0;
	while(!find){
		part = PM_GET_MEMBER_IN_SET(parts,sequence);
		part_type = PM_GET_OBJDATA(part,0,MMT_TAG_OBJTYPE);
		if(part_type == "2" | part_type == "3"){
			find=1;
		}
		sequence = sequence + 1;
	}
		
	/*抽取管段所属系统的表面处理定义，如果没有设置，则默认为镀锌*/
	surface_treatment = PM_GET_OBJDATA(part,0,Tag_System_SurfTreatOut);
	if(ISSTRING(surface_treatment)){
	   return(surface_treatment);
	} 
	else{
	    return("镀锌");
	}
}

get_def_pressure_test(handle object_handle)
{
	parts = PM_GET_OBJECTS_IN_GROUP(object_handle);
	part_number = PM_NR_MEMBERS_IN_SET(parts);
	find = 0;
	sequence = 0;
	while(!find){
		part = PM_GET_MEMBER_IN_SET(parts,sequence);
		part_type = PM_GET_OBJDATA(part,0,MMT_TAG_OBJTYPE);
		if(part_type == "2" | part_type == "3"){
			find=1;
		}
		sequence = sequence + 1;
	}
	
	/*抽取管段所属系统的试验压力，如果没有设置，则默认为0*/
	pressure = PM_GET_OBJDATA(part,0,Tag_System_TestPressure);
	if(ISSTRING(pressure)){
	   return(pressure);
	}
	else{
	    return("0");
	}
}

get_def_spool_type(handle object_handle)
{
	return("PRE");
}

get_def_spool_name(handle object_handle)
{	
	spool_number = PM_GET_OBJDATA(object_handle, 0, MMT_COSA_SPOOL_NAME);
	parts = PM_GET_OBJECTS_IN_GROUP(object_handle);
	part_number = PM_NR_MEMBERS_IN_SET(parts);
	find = 0;
	sequence = 0;
	while(!find){
		part = PM_GET_MEMBER_IN_SET(parts,sequence);
		part_type = PM_GET_OBJDATA(part,0,MMT_TAG_OBJTYPE);
		if(part_type == "2" | part_type == "3"){
			find=1;
		}
		sequence = sequence + 1;
	}
	
	/*修正腹板管线名无法获取及归属不同系统的问题*/
	line_name = PM_GET_OBJDATA(part, 0, MMT_TAG_PIPELINE_NAME);
	if(ISSTRING(line_name)){
	    pipe_line = line_name;
	}
	else{
	    pipe_line = "999";
	}
	
	spool_name = pipe_line + "-" + spool_number;
	return(spool_name);
}

/*获取管段重量*/
Get_Pipe_Spool_Weight(spool)
{
   pipes = PM_GET_OBJECTS_IN_GROUP(spool);
   pipe_number = PM_NR_MEMBERS_IN_SET(pipes);
   total_weight = 0.0;
   for(i=0;i<pipe_number;i=i+1;){
      pipe = PM_GET_MEMBER_IN_SET(pipes,i);
      part_number = PM_NR_PARTS_IN_PIPE(pipe);
      if(part_number != -1){
         for(nth=1;nth<=part_number;nth=nth +1;){            
            weight_s = PM_GET_OBJDATA(pipe,nth,MMT_TAG_MASS);
            weight = String_To_Float(weight_s);
            total_weight = total_weight + weight;
         }
      }
      /*标准件*/
      else{
         weight_s = PM_GET_OBJDATA(pipe,0,MMT_TAG_MASS);
         weight = String_To_Float(weight_s);
         total_weight = total_weight + weight;         
      }
   }
   return(total_weight);
}
