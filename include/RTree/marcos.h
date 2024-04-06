
#define BIND_PARM(PARM, ATTRIBUTE) Graphic_parm.PARM = &(ATTRIBUTE)
#define SET_PARM(PARM, VALUE) *Graphic_parm.PARM = VALUE
#define GET_PARM(PARM) (*Graphic_parm.PARM)
#define SET_PARM_ARRAY(PARM, SRC, LEN) memcpy(Graphic_parm.PARM, SRC, LEN)

#define ALLOC_MEMORY(type,target,size) (type *)Ralloc(size);\
                        if(target == NULL){\
                            glob_gllib_alloc_error = 1;\
                            return NULL;\
                        }\

#define add_component(widget, p_component)\
        add_component_func(widget, p_component);\

#define DefComponet(name, type)  \
        Gcomponent loc_##name = \
        {.e_component_type = type,\
        .u_element= {\
            .U_G##type  \

#define PrimitiveAttr   =
#define AppearanceAttr }, \
        .s_g =

#define EndComponent(name) , \
        .p_next = name->p_next, \
        .p_firstchild= name->p_firstchild,   \
        .p_parent=name->p_parent};\
        *name = loc_##name;\

#define DefGraphicPart(name)    \
        s_index=0u;  \
        c_stack_1[s_index]=NULL;


#define EndGraphicPart(name)    \
        name=tempComp_engine_addr1;

#define DefLayerGraphic(layer)    \
        current_primitive_List = &(layer->root);  \
        s_index=0u;  \
        c_stack_1[s_index]=NULL;


#define EndLayerGraphic(name)    \
        *current_primitive_List=tempComp_engine_addr1;   \
        current_primitive_List = NULL;




#define SubComponent(container, type) \
        tempComp_engine_addr = Ralloc(sizeof(Gcomponent));\
        container = link_component_fortest(c_stack_1[s_index], tempComp_engine_addr,next_op); \
        if(!c_stack_1[0]) \
            tempComp_engine_addr1=tempComp_engine_addr;   \
        c_stack_1[s_index]=container;    \
        next_op=ADD_LW;     \
        s_index++; c_stack_1[s_index]=container;    \



#define EndSubComponent(container)  \
        s_index--; \
        next_op=EXTENSION_LW;

#define Component(component) \
        tempComp_engine_addr = Ralloc(sizeof(Gcomponent));\
        component = link_component_fortest(c_stack_1[s_index], tempComp_engine_addr,next_op); \
        if(!c_stack_1[0]) \
            tempComp_engine_addr1=tempComp_engine_addr;   \
        c_stack_1[s_index]=component;    \
        next_op=EXTENSION_LW;     \


#define Reference(ref,compoent)    \
        Component(ref)           \
        ref->p_firstchild = compoent;     \
        ((Gcomponent *)addrconvert(compoent))->p_parent = (Gcomponent *)((char *)ref - (char *)RTree + RTree->baseAddr);

#define Component_Group(name, num)  \
        tempComp_engine_addr = Ralloc((num)*sizeof(Gcomponent));\
        name = link_component_fortest(c_stack_1[s_index], tempComp_engine_addr,next_op); \
        for(int i = 0; i < (num)-1; i++){    \
            Gcomponent *name_temp = link_component_fortest(addrconvert(tempComp_engine_addr+i), tempComp_engine_addr+i+1,EXTENSION_LW); \
        }\
        if(!c_stack_1[0]) \
            tempComp_engine_addr1=tempComp_engine_addr;   \
        c_stack_1[s_index]=((Gcomponent *)addrconvert(tempComp_engine_addr+(num)-1));    \
        next_op=EXTENSION_LW;     \

#define DefComponentGroup(name, id, type)   \
        Gcomponent loc_##name##_##id = \
        {.e_component_type = type,\
        .u_element= {\
            .U_G##type  \

#define EndComponentGroup(name, id) , \
        .p_next = name[id].p_next};\
        name[id] = loc_##name##_##id;\


#define UpdataComponent(name, type) \
        {   tempComp_engine_addr = name;    \
            G##type *currentElement = &((name)->u_element.U_G##type); \

#define New_PrimitiveAttr(Attr, Value)  \
        currentElement->Attr = Value;

#define New_AppearenceAttr(Attr, Value)  \
        tempComp_engine_addr->s_g.Attr = Value;

#define EndUpdate(name) \
        tempComp_engine_addr = NULL;}

#define SET_MESSAGE(VAL, type)       do{\
        *((type*)(currentAPP->MessageBuffer + currentAPP->message_ptr)) = VAL;\
        currentAPP->message_ptr += sizeof(type); \
        } while(0);


#define Update_AppearenceAttr(Attr, Value)  \
        SET_MESSAGE(0, char)    \
        SET_MESSAGE(app2engineAddr(&(tempComp_engine_addr->s_g.Attr)), char *)    \
        SET_MESSAGE(sizeof(tempComp_engine_addr->s_g.Attr), int)    \
        SET_MESSAGE(Value, typeof(tempComp_engine_addr->s_g.Attr))    \


#define Update_PrimitiveAttr(Attr, Value)  \
        SET_MESSAGE(0, char)    \
        SET_MESSAGE(app2engineAddr(&(currentElement->Attr)), char *)    \
        SET_MESSAGE(sizeof(currentElement->Attr), int)    \
        SET_MESSAGE(Value, typeof(currentElement->Attr))    \


#define REFDEFINE(x) \
    Gcomponent *x; \
    static x##_Graphic_Parm Graphic_parm;\
    void init_##x()


#define PARM_PARSE(x)  \
    void set_##x##_parm(struct x##_Graphic_Parm_s parm, Gcomponent* ref){\
        SET_MESSAGE(1, char)  \
        SET_MESSAGE(&ref, char *)       \
        char *length_ptr = currentAPP->message_ptr + currentAPP->MessageBuffer;   \
        ref->u_element.U_GReference.ub_para = currentAPP->message_ptr;\
        SET_MESSAGE(0, int)       \




#define END_PARM_PARSE(x) \
        *length_ptr =  currentAPP->message_ptr + currentAPP->MessageBuffer - length_ptr - sizeof(int);\
    }
