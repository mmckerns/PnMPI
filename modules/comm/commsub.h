#include <datatype.h>
#include <requests.h>

#if 0
#ifdef __cplusplus
extern "C" {
#endif
#endif

extern PNMPIMOD_Datatype_getReference_t dt_get;
extern PNMPIMOD_Datatype_delReference_t dt_del;
extern PNMPIMOD_Datatype_getSize_t dt_size;
extern int verbosity_level;

extern int pnmpimod_comm_collective_support;

extern PNMPIMOD_Requests_MapRequest_t PNMPIMOD_requestmap;


/*------------------------------------------------------------------*/
/* constants */

#define PNMPIMOD_COMM_IGNOREDATA         0x1
#define PNMPIMOD_COMM_KEEPCOLLECTIVE     0x2
#define PNMPIMOD_COMM_DISSOLVECOLLECTIVE 0x4
#define PNMPIMOD_COMM_REPLACECOLLECTIVE  0x8

#define PNMPIMOD_COMM_DEFAULT            PNMPIMOD_COMM_DISSOLVECOLLECTIVE|PNMPIMOD_COMM_KEEPCOLLECTIVE;


#define PNMPIMOD_COMM_COLLTYPEMASK 0x7
#define PNMPIMOD_COMM_P2P          0x0
#define PNMPIMOD_COMM_ASYNC_P2P    0x1
#define PNMPIMOD_COMM_COLL_FANIN   0x2
#define PNMPIMOD_COMM_COLL_FANOUT  0x3
#define PNMPIMOD_COMM_COLL_ALL2ALL 0x4
#define PNMPIMOD_COMM_COLL_OTHER   0x5
#define PNMPIMOD_COMM_COLL_BARRIER 0x6

#define PNMPIMOD_COMM_COLLREDMASK  0x8
#define PNMPIMOD_COMM_COLL_REDUCE  0x8

#define PNMPIMOD_COMM_COLLOPMASK     0xF0
#define PNMPIMOD_COMM_BARRIER        0x10
#define PNMPIMOD_COMM_BCAST          0x20
#define PNMPIMOD_COMM_GATHER         0x30
#define PNMPIMOD_COMM_GATHERV        0x40
#define PNMPIMOD_COMM_SCATTER        0x50
#define PNMPIMOD_COMM_SCATTERV       0x60
#define PNMPIMOD_COMM_ALLGATHER      0x70
#define PNMPIMOD_COMM_ALLGATHERV     0x80
#define PNMPIMOD_COMM_ALL2ALL        0x90
#define PNMPIMOD_COMM_ALL2ALLV       0xA0
#define PNMPIMOD_COMM_REDUCE         0xB0
#define PNMPIMOD_COMM_REDUCESCATTER  0xC0
#define PNMPIMOD_COMM_ALLREDUCE      0xD0
#define PNMPIMOD_COMM_SCAN           0xE0

#define PNMPIMOD_COMM_TESTWAITMASK   0x100
#define PNMPIMOD_COMM_COMPLETEMASK   0x600
#define PNMPIMOD_COMM_TEST           0x000
#define PNMPIMOD_COMM_WAIT           0x100
#define PNMPIMOD_COMM_ONE            0x000
#define PNMPIMOD_COMM_ANY            0x200
#define PNMPIMOD_COMM_SOME           0x400
#define PNMPIMOD_COMM_ALL            0x600

#define PNMPIMOD_COMM_NOMSG          ((void*) 0)
#define PNMPIMOD_COMM_FOUNDMSG       ((void*) 1)

#define PNMPIMOD_COMM_COLLTAG        4243


/*------------------------------------------------------------------*/
/* module internal support routines */

void pnmpimod_comm_set_collectivesupport(int param);


/*------------------------------------------------------------------*/
/* callback prototypes */

#ifdef SUBMODNAME
#include <string.h>
char *provide_submod_name() { return strdup(SUBMODNAME); }
#else
char *provide_submod_name();
#endif
void COMM_ALL_INIT(int argc, char**argv);
void COMM_ALL_PREINIT(int argc, char**argv);
void PRE_COMM_ALL_INIT(int argc, char**argv);
void COMM_ALL_FINALIZE();

void SEND_P2P_START(
#ifdef HAVE_MPI3_CONST_ARGS
    const
#endif // HAVE_MPI3_CONST_ARGS
    void *buf, int count, MPI_Datatype dt, int node, int tag, 
		    MPI_Comm comm, void **ptr, int type);
void SEND_P2P_ASYNC_MID1(
#ifdef HAVE_MPI3_CONST_ARGS
    const
#endif // HAVE_MPI3_CONST_ARGS
    void *buf, int count, MPI_Datatype dt, int node, int tag, 
			 MPI_Comm comm, void **ptr, int type);
void SEND_P2P_END(
#ifdef HAVE_MPI3_CONST_ARGS
    const
#endif // HAVE_MPI3_CONST_ARGS
    void *buf, int count, MPI_Datatype dt, int node, int tag, 
		  MPI_Comm comm, int err, void **ptr, void **midptr, int type);

void RECV_P2P_START(void *buf, int count, MPI_Datatype dt, int node, int tag, 
		    MPI_Comm comm, void **ptr, int type);
void RECV_P2P_ASYNC_MID1(void *buf, int count, MPI_Datatype dt, int node, int tag, 
			 MPI_Comm comm, int err, void **ptr, int type);
void RECV_P2P_END(void *buf, int count, MPI_Datatype dt, int node, int tag, 
                  MPI_Comm comm, int err, void **ptr, void **midptr, int type, 
                  MPI_Status *status, int numindex, int index);

void COMM_P2P_ASYNC_MID2(int count, MPI_Request *requests, int flag, void **midptr);
void COMM_P2P_ASYNC_COMPLETION(int type);

void COMM_COLL_REDUCE(void *buf, int count, MPI_Datatype dt, MPI_Op ops, int size, void** ptr);

void COMM_COLL_START(MPI_Comm comm,int root,int type, void **ptr);
void COMM_COLL_END(MPI_Comm comm,int root,int type, void **ptr);

#if 0
#ifdef __cplusplus
}
#endif
#endif
