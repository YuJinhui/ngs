/*===========================================================================
*
*                            PUBLIC DOMAIN NOTICE
*               National Center for Biotechnology Information
*
*  This software/database is a "United States Government Work" under the
*  terms of the United States Copyright Act.  It was written as part of
*  the author's official duties as a United States Government employee and
*  thus cannot be copyrighted.  This software/database is freely available
*  to the public for use. The National Library of Medicine and the U.S.
*  Government have not placed any restriction on its use or reproduction.
*
*  Although all reasonable efforts have been taken to ensure the accuracy
*  and reliability of the software and data, the NLM and the U.S.
*  Government do not and cannot warrant the performance or results that
*  may be obtained by using this software or data. The NLM and the U.S.
*  Government disclaim all warranties, express or implied, including
*  warranties of performance, merchantability or fitness for any particular
*  purpose.
*
*  Please cite the author in any work or product based on this material.
*
* ===========================================================================
*
*/

#ifndef _hpp_ngs_alignment_
#define _hpp_ngs_alignment_

#ifndef _hpp_ngs_fragment_
#include <ngs/Fragment.hpp>
#endif

namespace ngs
{

    /*----------------------------------------------------------------------
     * forwards and typedefs
     */
    typedef FragmentRef AlignmentRef;


    /*======================================================================
     * Alignment
     *  represents an alignment between a Fragment and Reference sub-sequence
     *  provides a path to Read and mate Alignment
     */
    class Alignment : public Fragment
    {
    public:

        /* getAlignmentId
         *  retrieve an identifying String that can be used for later access.
         *  the id will be unique within ReadCollection.
         */
        StringRef getAlignmentId () const
            throw ( ErrorMsg );


        /*------------------------------------------------------------------
         * Reference
         */

        /* getReferenceSpec
         */
        String getReferenceSpec () const
            throw ( ErrorMsg );

        /* getMappingQuality 
         */
        int getMappingQuality () const
            throw ( ErrorMsg );

        /* getReferenceBases
         *  return reference bases
         */
        StringRef getReferenceBases () const
            throw ( ErrorMsg );


        /*------------------------------------------------------------------
         * Fragment
         */

        /* getReadGroup
         */
        String getReadGroup () const
            throw ( ErrorMsg );

        /* getReadId
         */
        StringRef getReadId () const
            throw ( ErrorMsg );

        /* getClippedFragmentBases
         *  return fragment bases
         */
        StringRef getClippedFragmentBases () const
            throw ( ErrorMsg );

        /* getClippedFragmentQualities
         *  return fragment phred quality values
         *  using ASCII offset of 33
         */
        StringRef getClippedFragmentQualities () const
            throw ( ErrorMsg );

        /* getAlignedFragmentBases
         *  return fragment bases in their aligned orientation
         */
        StringRef getAlignedFragmentBases () const
            throw ( ErrorMsg );

        /*------------------------------------------------------------------
         * details of this alignment
         */

        /* AlignmentFilter
         *  values should be or'd together to produce filter bits
         */
        enum AlignmentFilter
        {
            passFailed = 1,         // reads rejected due to platform/vendor quality criteria
            passDuplicates = 2,     // either a PCR or optical duplicate
            minMapQuality = 4,      // pass alignments with mappingQuality >= param
            maxMapQuality = 8,      // pass alignments with mappingQuality <= param
            noWraparound = 16,      // do not include leading wrapped around alignments to circular references
            startWithinSlice = 32   // change slice intersection criteria so that start pos is within slice
        };

        /* AlignmentCategory
         */
        enum AlignmentCategory
        {
            primaryAlignment = 1,
            secondaryAlignment = 2,
            all = primaryAlignment | secondaryAlignment
        };
        
        /* getAlignmentCategory
         *  alignments are categorized as primary or secondary (alternate).
         *  return an AlignmentCategory
         *  throws ErrorMsg if the property cannot be retrieved
         */
        AlignmentCategory getAlignmentCategory () const
            throw ( ErrorMsg );

        /* getAlignmentPosition
         *  retrieve the Alignment's starting position on the Reference
         *  return 0-based offset from start of Reference
         *  throws ErrorMsg if the property cannot be retrieved
         */
        int64_t getAlignmentPosition () const
            throw ( ErrorMsg );

        /* getReferencePositionProjectionRange
         *  retrieve the projection of Reference position on the Alignment
         *  ref_pos - 0-based offset from start of Reference
         *  returns a packed 64bit value:
         *   -upper 32bits represent a 0-based offset from start of the Alignment
         *    corresponding to ref_pos (beginning of the insertion in the case ref_pos
         *    projects on the insertion)
         *   -lower 32bits represent the length of the ref_pos projection on the 
         *    Alignment: e.g. 1 - match/mismatch, 0 - ref_pos is within the
         *    region deleted from the Alignment, > 1 - there is an insertion
         *    on the Alignment so ref_pos can be projected anywhere from the
         *    beginning of that insertion to the end of it.
         *  throws ErrorMsg if the property cannot be retrieved
         */
        uint64_t getReferencePositionProjectionRange ( int64_t ref_pos ) const
            throw ( ErrorMsg );

        /* getAligmentLength
         *  retrieve the projected length of an Alignment projected upon Reference.
         *  return unsigned length of projection
         *  throws ErrorMsg if the property cannot be retrieved
         */
        uint64_t getAlignmentLength () const
            throw ( ErrorMsg );

        /* getIsReversedOrientation
         *  test if orientation is reversed with respect to the Reference sequence.
         *  return true if reversed
         *  throws ErrorMsg if the property cannot be retrieved
         */
        bool getIsReversedOrientation () const
            throw ( ErrorMsg );

        /* ClipEdge
         */
        enum ClipEdge
        {
            clipLeft  = 0,
            clipRight = 1
        };

        /* getSoftClip
         */
        int getSoftClip ( ClipEdge edge ) const
            throw ( ErrorMsg );

        /* getTemplateLength
         */
        uint64_t getTemplateLength () const
            throw ( ErrorMsg );

        /* getShortCigar
         *  returns a text string describing alignment details
         */
        StringRef getShortCigar ( bool clipped ) const
            throw ( ErrorMsg );

        /* getLongCigar
         *  returns a text string describing alignment details
         */
        StringRef getLongCigar ( bool clipped ) const
            throw ( ErrorMsg );

        /* getRNAOrientation
         *  returns '+' if positive strand is transcribed
         *  returns '-' if negative strand is transcribed
         *  returns '?' if unknown
         */
        char getRNAOrientation () const
            throw ( ErrorMsg );


        /*------------------------------------------------------------------
         * details of mate alignment
         */
         
        /* hasMate
         */
        bool hasMate () const
            throw ();

        /* getMateAlignmentId
         */
        StringRef getMateAlignmentId () const
            throw ( ErrorMsg );

        /* getMateAlignment
         */
        Alignment getMateAlignment () const
            throw ( ErrorMsg );

        /* getMateReferenceSpec
         */
        String getMateReferenceSpec () const
            throw ( ErrorMsg );

        /* getMateIsReversedOrientation
         */
        bool getMateIsReversedOrientation () const
            throw ( ErrorMsg );

    public:

        // C++ support

        Alignment & operator = ( AlignmentRef ref )
            throw ();
        Alignment ( AlignmentRef ref )
            throw ();

        Alignment & operator = ( const Alignment & obj )
            throw ( ErrorMsg );
        Alignment ( const Alignment & obj )
            throw ( ErrorMsg );

        ~ Alignment ()
            throw ();
    };

} // namespace ngs


// inlines
#ifndef _inl_ngs_alignment_
#include <ngs/inl/Alignment.hpp>
#endif

#endif // _hpp_ngs_alignment_
