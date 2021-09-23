

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Fri Dec 04 19:28:08 2015
 */
/* Compiler settings for .\AxWrapper1.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __AxWrapper1idl_h__
#define __AxWrapper1idl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DEsdAdvancedGraphControl_FWD_DEFINED__
#define ___DEsdAdvancedGraphControl_FWD_DEFINED__
typedef interface _DEsdAdvancedGraphControl _DEsdAdvancedGraphControl;
#endif 	/* ___DEsdAdvancedGraphControl_FWD_DEFINED__ */


#ifndef ___DEsdAdvancedGraphControlEvents_FWD_DEFINED__
#define ___DEsdAdvancedGraphControlEvents_FWD_DEFINED__
typedef interface _DEsdAdvancedGraphControlEvents _DEsdAdvancedGraphControlEvents;
#endif 	/* ___DEsdAdvancedGraphControlEvents_FWD_DEFINED__ */


#ifndef __EsdAdvancedGraphControl_FWD_DEFINED__
#define __EsdAdvancedGraphControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class EsdAdvancedGraphControl EsdAdvancedGraphControl;
#else
typedef struct EsdAdvancedGraphControl EsdAdvancedGraphControl;
#endif /* __cplusplus */

#endif 	/* __EsdAdvancedGraphControl_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_AxWrapper1_0000_0000 */
/* [local] */ 

typedef /* [public][helpstring][version][uuid] */  DECLSPEC_UUID("81BFD04B-203D-4002-9040-90E59B172C81") 
enum __MIDL___MIDL_itf_AxWrapper1_0000_0000_0001
    {	zdHorizontal	= 0,
	zdVertical	= 1,
	zdBoth	= 2
    } 	EZoomDirection;



extern RPC_IF_HANDLE __MIDL_itf_AxWrapper1_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AxWrapper1_0000_0000_v0_0_s_ifspec;


#ifndef __EsdAdvancedGraphControlLib_LIBRARY_DEFINED__
#define __EsdAdvancedGraphControlLib_LIBRARY_DEFINED__

/* library EsdAdvancedGraphControlLib */
/* [control][helpstring][helpfile][version][uuid] */ 

typedef /* [public][helpstring][version][uuid] */  DECLSPEC_UUID("85401CED-A42E-4728-A82F-B0398CEBC208") struct __MIDL___MIDL_itf_AxWrapper1_0000_0000_0002
    {
    DWORD dwEventCode;
    DOUBLE dblStartTime;
    DOUBLE dblEndTimeOrValue;
    } 	stEventInfo;


EXTERN_C const IID LIBID_EsdAdvancedGraphControlLib;

#ifndef ___DEsdAdvancedGraphControl_DISPINTERFACE_DEFINED__
#define ___DEsdAdvancedGraphControl_DISPINTERFACE_DEFINED__

/* dispinterface _DEsdAdvancedGraphControl */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DEsdAdvancedGraphControl;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("9117C567-1EAD-48B3-BA9E-C4D44852D181")
    _DEsdAdvancedGraphControl : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DEsdAdvancedGraphControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DEsdAdvancedGraphControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DEsdAdvancedGraphControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DEsdAdvancedGraphControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DEsdAdvancedGraphControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DEsdAdvancedGraphControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DEsdAdvancedGraphControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DEsdAdvancedGraphControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DEsdAdvancedGraphControlVtbl;

    interface _DEsdAdvancedGraphControl
    {
        CONST_VTBL struct _DEsdAdvancedGraphControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DEsdAdvancedGraphControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DEsdAdvancedGraphControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DEsdAdvancedGraphControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DEsdAdvancedGraphControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DEsdAdvancedGraphControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DEsdAdvancedGraphControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DEsdAdvancedGraphControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DEsdAdvancedGraphControl_DISPINTERFACE_DEFINED__ */


#ifndef ___DEsdAdvancedGraphControlEvents_DISPINTERFACE_DEFINED__
#define ___DEsdAdvancedGraphControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DEsdAdvancedGraphControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DEsdAdvancedGraphControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("07A82910-34BC-43C2-ADAE-A462286D4E10")
    _DEsdAdvancedGraphControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DEsdAdvancedGraphControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DEsdAdvancedGraphControlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DEsdAdvancedGraphControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DEsdAdvancedGraphControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DEsdAdvancedGraphControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DEsdAdvancedGraphControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DEsdAdvancedGraphControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DEsdAdvancedGraphControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DEsdAdvancedGraphControlEventsVtbl;

    interface _DEsdAdvancedGraphControlEvents
    {
        CONST_VTBL struct _DEsdAdvancedGraphControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DEsdAdvancedGraphControlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DEsdAdvancedGraphControlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DEsdAdvancedGraphControlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DEsdAdvancedGraphControlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DEsdAdvancedGraphControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DEsdAdvancedGraphControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DEsdAdvancedGraphControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DEsdAdvancedGraphControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_EsdAdvancedGraphControl;

#ifdef __cplusplus

class DECLSPEC_UUID("E98E4ED3-C038-4705-8EAB-43AD8A1B75AB")
EsdAdvancedGraphControl;
#endif
#endif /* __EsdAdvancedGraphControlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


