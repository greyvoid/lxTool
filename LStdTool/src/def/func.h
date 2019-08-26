
#ifndef __FUNC_H__
#define __FUNC_H__


#define PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const;

#define PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void);\
public: virtual void set##funName(varType var);


#define SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }


#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

#define SETGETCONST(varType, varName, funName)\
protected: varType varName; \
public:  varType funName(void) const { return varName; }\
public: void set##funName(varType var){ varName = var; }

#define SETGET(varType, varName, funName)\
protected: varType varName; \
public:  varType funName(void) { return varName; }\
public: void set##funName(varType var){ varName = var; }





#endif //__FUNC_H__
