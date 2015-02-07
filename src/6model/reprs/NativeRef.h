/* Representation of a reference to a native value. */
struct MVMNativeRefBody {
    union {
        struct {
            MVMFrame *frame;
            MVMRegister *var;
        } lexical;
        struct {
            MVMObject *obj;
            MVMObject *class_handle;
            MVMString *name;
        } attribute;
        struct {
            MVMObject *obj;
            MVMint64 idx;
        } positional;
    } u;
};
struct MVMNativeRef {
    MVMObject common;
    MVMNativeRefBody body;
};

/* Kinds of native reference. */
#define MVM_NATIVEREF_LEXICAL       1
#define MVM_NATIVEREF_ATTRIBUTE     2
#define MVM_NATIVEREF_POSITIONAL    3

/* REPR data for a native reference. */
struct MVMNativeRefREPRData {
    /* The primitive type of native reference this is (one of the values that
     * is valid for MVMStorageSpec.boxed_primitive). */
    MVMuint16 primitive_type;

    /* The kind of reference this is. */
    MVMuint16 ref_kind;
};

/* Function for REPR setup. */
const MVMREPROps * MVMNativeRef_initialize(MVMThreadContext *tc);

/* Operations on a nativeref REPR. */
void MVM_nativeref_ensure(MVMThreadContext *tc, MVMObject *val, MVMuint16 wantprim, MVMuint16 wantkind, char *guilty);
MVMObject * MVM_nativeref_attr_i(MVMThreadContext *tc, MVMObject *obj, MVMObject *class_handle, MVMString *name);
MVMObject * MVM_nativeref_attr_n(MVMThreadContext *tc, MVMObject *obj, MVMObject *class_handle, MVMString *name);
MVMObject * MVM_nativeref_attr_s(MVMThreadContext *tc, MVMObject *obj, MVMObject *class_handle, MVMString *name);