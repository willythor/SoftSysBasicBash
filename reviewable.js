// These variables are provided by the reviewable environment.
// For debugging, we import these functions and created a sample json PR using the info
// in: https://github.com/Reviewable/Reviewable/wiki/FAQ
// import _ from 'lodash';
// import review from './sample_pr.json';

const numReviewersRequired = 1;

const files = {};
const assignees = _(review.pullRequest.assignees).map('username')
  .without(review.pullRequest.author.username).value();
const willyanddave = ['willythor', 'davidabrahams'];

_.each(review.files, file => {
  const reviewInfo = {};
  // reviewers are all people who submitted reviews on the last file revision , other than
  // the PR author, who are also assignees
  const reviewers = _(_.last(file.revisions).reviewers)
    .map('username')
    .filter(u => _.includes(assignees, u))
    .value();

  // iterate over revisions for each file
  _.each(file.revisions, revision => {
    // calculate number of reviewers this revision by dropping pr author and taking length of
    // reviewers
    const reviewersThisRevision = _(revision.reviewers)
      .map('username')
      .filter(u => _.includes(assignees, u))
      .value();
    // mark this revision as unreviewed the number of reviews is not high enough
    revision.reviewed = reviewersThisRevision.length >= numReviewersRequired;
  });

  const neededReviewers = [];
  if (reviewers.length < numReviewersRequired) {
    // place all non-author willyanddave members who haven't reviewed the file and add them
    // to neededReviewers
    _.each(_(assignees)
      .reject(a => _.includes(reviewers, a))
      .value(), r => neededReviewers.push(r));
  }
  reviewInfo.neededReviewers = neededReviewers;
  reviewInfo.numReviewsLeft = Math.max(0, numReviewersRequired - reviewers.length);
  reviewInfo.revision = _.last(file.revisions).key;
  files[file.path] = reviewInfo;
});

// map from willyanddave member to the number of discussions they must resolve
const discussions = {};
_.each(willyanddave, c => { discussions[c] = 0; });
_.each(_(review.discussions)
  .map('participants')
  .flatten()
  .filter({ resolved: false })
  .value(),
  d => { discussions[d.username] += 1; });

const unresolvedDiscussions = _.pick(discussions, o => o > 0);
let completed = _(files)
  // no files have reviews remaining
  .values()
  .map('numReviewsLeft')
  .map(c => c === 0)
  .every()
  &&
  // no discussions are unresolved
  !_(discussions)
  .values()
  .some();

const shortReasons = [];
for (let i = 1; i <= numReviewersRequired; i++) {
  const numFiles = _(files).keys().filter(f => files[f].numReviewsLeft === i).value().length;
  if (numFiles) {
    // N file(s) need(s) M review(s)
    shortReasons.push(numFiles.toString() + ' file' + (numFiles > 1 ? 's' : '') + ' need' +
      (numFiles === 1 ? 's ' : ' ') + i.toString() + ' review' + (i > 1 ? 's' : ''));
  }
}
if (!_.isEmpty(unresolvedDiscussions)) {
  const pendingChauncies = _.keys(unresolvedDiscussions);
  shortReasons.push(pendingChauncies.join(', ') + ' must resolve discussions');
}

const longReasons = [];

_.each(willyanddave, c => {
  const filesToReview = _(files)
    .keys()
    // files where this willyanddave needs to review it
    .filter(f => _.includes(files[f].neededReviewers, c))
    // and there are reviews required
    .filter(f => files[f].numReviewsLeft)
    .value();
  if (filesToReview.length) {
    longReasons.push(c + ' must review ' + filesToReview.length + ' file' + (filesToReview.length > 1 ? 's' : ''));
  }
});

_.each(_.keys(discussions),
  c => {
    if (discussions[c])
      longReasons.push(c + ' must resolve ' + discussions[c] + ' discussion' + (discussions[c] > 1 ? 's' : ''));
  }
);

if (review.pullRequest.target.branch !== 'master') {
  completed = false;
  shortReasons.push('target branch is not master');
  longReasons.push('target branch is not master');
}


const reviewableStatus = {
  completed,
  description: longReasons.join(', '),
  shortDescription: shortReasons.join(', '),
  files: review.files,
};

// console.log(reviewableStatus);

return reviewableStatus;
